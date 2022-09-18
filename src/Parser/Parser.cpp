//
// Created by mythi on 21/07/22.
//

#include <fstream>

#include "magic_enum.hpp"

#include "Parser.h"
#include "Constants.h"


#define EXPECT(lexeme) if(!match(lexeme)) {return fmt::format("Expected {} Found {}",lexeme.to_string(),peek().to_string());}else{advance();}

#define SWALLOW(lexeme) if(match(lexeme)) {advance();}

namespace hasha {
    Parser::Parser(std::string file_name, ScopeTree::Ptr scope_tree) :
            scope_tree(std::move(scope_tree)),
            lexer(std::move(file_name)),
            cursor(0) {

        auto res = lexer.lex();
        if (res.is_error()) {
            fmt::print("{}\n", res.error());
            exit(1);
        } else {

            lexemes = lexer.get_lexemes();
        }
        set_context(Context{});
    }

    ErrorOr<Block::Ptr> Parser::parse() {

        auto blk = TRY(block(scope_tree->create_scope()));

        std::ofstream ojson("parser_output.json");
        if (ojson.is_open()) {
            ojson << blk->to_string();
        }

        return blk;

    }

    Lexeme Parser::peek(std::size_t k) const noexcept {

        if (cursor + k < lexemes.size()) return lexemes[cursor + k];

        return lexemes.back();
    }

    bool Parser::done(int k) const noexcept {

        if (cursor + k >= lexemes.size() || cursor + k < 0)
            return true;

        return false;
    }

    Lexeme Parser::advance(int k) noexcept {

        if (!done(k)) {
            cursor += k;
            return lexemes[cursor];
        }

        return lexemes.back();
    }

    ErrorOr<Identifier::Ptr>
    Parser::identifier(Scope &scope, bool check_for_redefiniton, bool register_to_scope) noexcept {

        const auto name = peek().data();

        if (check_for_redefiniton) {
            if (scope.identifiers.contains(name)) {
                return fmt::format(
                        "Identifier {} has already been defined in this scope, line: {},col: {} \n",
                        name,
                        peek().span().line,
                        peek().span().col
                );
            }
        }

        if (name.empty()) return "Failed to parse identifier name";

        if (std::isdigit(name[0])) return "An identifier cannot start with a digit";

        auto is_legal = [](char c) -> bool {
            return std::isalnum(c) || c == '_';
        };
        for (const auto &ch: name) {
            if (!is_legal(ch)) {
                return fmt::format("Illegal character {}", ch);
            }
        }

        advance();

        auto x = Identifier::create(name, peek(-1).span());

        if (register_to_scope) {
            scope.identifiers[name] = x.get();
        }

        return x;
    }

    ErrorOr<Type::Ptr> Parser::type() noexcept {

        auto type_name = peek().data();

        if (type_name.empty()) return "Failed to parse type name";

        if (std::isdigit(type_name[0])) return "A type cannot start with a digit";

        auto is_legal = [](char c) -> bool {
            return std::isalnum(c) || c == '_';
        };
        for (const auto &ch: type_name) {
            if (!is_legal(ch)) {
                return fmt::format("Illegal character {}", ch);
            }
        }
        auto before_span = peek().span();
        advance();

        if (match(LANGEL)) {
            SWALLOW(LANGEL)
            auto type_list = TypeList{};
            while (!match(RANGEL) && !match(SEMICOLON)) {
                SWALLOW(COMMA)
                type_list.push_back(TRY(type()));
            }
            if (type_list.empty())
                return fmt::format(
                        "Generic Type {} with no type list, line: {}, col: {}",
                        type_name,
                        before_span.line,
                        before_span.col
                );

            EXPECT(RANGEL)
            auto after_span = peek(-1).span();


            return GenericType::create(
                    type_name,
                    before_span,
                    std::move(type_list),
                    Span{
                            before_span.begin,
                            after_span.end,
                            before_span.line,
                            before_span.col
                    }
            );

        }

        return Type::create(type_name, peek(-1).span());
    }

    ErrorOr<Parameter::Ptr> Parser::parameter(Scope &scope) {

        auto b_span = peek().span();
        auto name = TRY(identifier(scope));
        EXPECT(COLON)
        auto param_type = TRY(type());

        SWALLOW(COMMA)

        b_span.set_end(peek(-1).span().end);
        return Parameter::create(std::move(param_type), *name, b_span);
    }


    ErrorOr<Expression::Ptr> Parser::parse_expression(Scope &scope, const Lexeme &delimiter) {

        std::deque<Lexeme> operators; // stack
        auto token_list = TokenList{};

        set_context(current_context().set_parsing_expression(true));

        auto begin_span = peek().span();

        while (!match(delimiter)) {

            if (match(Patterns::FunctionCall)) {
                token_list.push_back(TRY(function_call(scope, true)));
                continue;
            }

            auto x = peek();

            if (current_context().parsing_args && x == RPAREN)
                break;
            if (current_context().parsing_args && x == COMMA)
                break;

            advance();
            if (x.type() == LexemeType::OPERATOR) {
                while (!operators.empty() && operators.front().type() == LexemeType::OPERATOR) {
                    auto y = operators.front();

                    if ((x.associativity() == Associativity::LEFT &&
                         x.precedence() <= y.precedence()) ||
                        (x.associativity() == Associativity::RIGHT &&
                         x.precedence() < y.precedence())) {

                        token_list.push_back(Operator::create(y.data(), y.span()));
                        operators.pop_front();

                    } else {
                        break;
                    }

                }
                operators.push_front(x);
            } else if (x == LPAREN) {
                operators.push_front(x);
            } else if (x == RPAREN) {
                while (operators.front() != LPAREN) {
                    // TODO: If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                    if (operators.empty()) break;
                    token_list.push_back(Operator::create(operators.front().data(), operators.front().span()));
                    operators.pop_front();
                }
                // TODO: If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                if (operators.front() != LPAREN)
                    break;
                operators.pop_front();
            } else {
                if (x != COMMA) {
                    switch (x.type()) {
                        case LexemeType::NUMERIC_LITERAL:
                            token_list.push_back(NumericLiteral::create(x.data(), x.span()));
                            break;
                        case LexemeType::STRING_LITERAL:
                            token_list.push_back(StringLiteral::create(x.data(), x.span()));
                            break;
                        case LexemeType::BOOLEAN_LITERAL:
                            token_list.push_back(BooleanLiteral::create(x.data(), x.span()));
                            break;
                        case LexemeType::IDENTIFIER: {
                            advance(-1);
                            auto idn = TRY(identifier(scope, false, false));
                            if (!scope.is_identifier_in_scope(idn->get())) {
                                return fmt::format(
                                        "Identifier {} is undefined in this scope, line: {}, col {}",
                                        idn->get(),
                                        idn->span().line,
                                        idn->span().col
                                );
                            }
                            token_list.push_back(std::move(idn));
                        }
                            break;
                        default:
                            return fmt::format(
                                    "Unknown token {} in expression, line: {} col: {}\n",
                                    x.to_string(),
                                    x.span().line,
                                    x.span().col
                            );
                    }
                }
            }
        }

        while (!operators.empty()) {
            token_list.push_back(Operator::create(operators.front().data(), operators.front().span()));
            operators.pop_front();
        }

        restore_context();
        auto end_span = peek(-1).span();

        if (current_context().parsing_return_expression) {
            return ReturnExpression::create(
                    std::move(token_list),
                    Span{begin_span.begin, end_span.end, begin_span.line, begin_span.col}
            );
        }

        return Expression::create(
                std::move(token_list),
                Span{begin_span.begin, end_span.end, begin_span.line, begin_span.col}
        );

    }


    ErrorOr<ExpressionList>
    Parser::parse_multiple(Scope &scope, const Lexeme &left, const Lexeme &right, const Lexeme &separator) {


        EXPECT(left)

        auto exprs = ExpressionList{};

        while (!match(right)) {
            SWALLOW(separator)
            exprs.push_back(TRY(parse_expression(scope)));
        }
        EXPECT(right)

        return exprs;
    }

    ErrorOr<IfStatement::Ptr> Parser::if_statement(Scope &scope) {

        auto span = peek().span();
        EXPECT(IF)
        auto condition = TRY(parse_expression(scope, LCURLY));
        EXPECT(LCURLY)
        auto blk = TRY(block(scope_tree->create_scope(scope.id)));
        EXPECT(RCURLY)

        return IfStatement::create(
                std::move(condition),
                std::move(blk),
                span
        );
    }

    ErrorOr<ElifStatement::Ptr> Parser::elif_statement(Scope &scope) {


        auto span = peek().span();
        EXPECT(ELIF)
        auto condition = TRY(parse_expression(scope, LCURLY));
        EXPECT(LCURLY)
        auto blk = TRY(block(scope_tree->create_scope(scope.id)));
        EXPECT(RCURLY)

        return ElifStatement::create(
                std::move(condition),
                std::move(blk),
                span
        );
    }

    ErrorOr<ElseStatement::Ptr> Parser::else_statement(Scope &scope) {

        auto span = peek().span();
        EXPECT(ELSE)
        EXPECT(LCURLY)
        auto blk = TRY(block(scope_tree->create_scope(scope.id)));
        EXPECT(RCURLY)

        return ElseStatement::create(std::move(blk), span);
    }

    ErrorOr<Declaration::Ptr> Parser::declaration(Scope &scope) {

        auto before_span = peek().span();
        auto name = TRY(identifier(scope, true));
        EXPECT(COLON)
        auto decl_type = TRY(type());


        auto asx = TRY(parse_expression(scope));
        if (asx->empty()) {
            return fmt::format(
                    "Unintialized declaration of variable {} on line: {}, col: {}",
                    name->get(),
                    before_span.line,
                    before_span.col
            );
        }
        auto after_span = peek(-1).span();

        auto span = Span{
                before_span.begin,
                after_span.end,
                before_span.line,
                before_span.col
        };
        EXPECT(SEMICOLON)
        return Declaration::create(
                std::move(decl_type),
                *name,
                span,
                std::move(asx)
        );


    }

    ErrorOr<Block::Ptr> Parser::block(Scope &scope) noexcept {

        auto token_list = TokenList{};
        auto begin_span = peek().span();

        while (!match(RCURLY)) {

            // Parse the unambigous statements first
            if (match(FN)) {
                token_list.push_back(TRY(function(scope)));
            } else if (match(IF)) {
                token_list.push_back(TRY(if_statement(scope)));
            } else if (match(ELSE)) {

                if (!is_previous_of<IfStatement>(token_list) && !is_previous_of<ElifStatement>(token_list))
                    return "Rouge else statement";

                token_list.push_back(TRY(else_statement(scope)));
            } else if (match(ELIF)) {

                if (!is_previous_of<IfStatement>(token_list) && !is_previous_of<ElifStatement>(token_list))
                    return "Rouge elif statement";
                if (is_previous_of<ElseStatement>(token_list))
                    return "An else statement cannot be followed by and elif statement";

                token_list.push_back(TRY(elif_statement(scope)));
            } else if (match(Patterns::Declaration)) {
                token_list.push_back(TRY(declaration(scope)));
            } else if (match(Patterns::Assignment)) {
                token_list.push_back(TRY(assignment(scope)));
            } else if (match(RETURN)) {
                token_list.push_back(TRY(return_expression(scope)));
            } else {
                token_list.push_back(TRY(parse_expression(scope)));
                EXPECT(SEMICOLON)
            }
        }
        auto end_span = peek().span();
        auto span = Span{
                begin_span.begin,
                end_span.end,
                begin_span.line,
                begin_span.col
        };
        return Block::create(std::move(token_list), span);
    }

    ErrorOr<Function::Ptr> Parser::function(Scope &scope) {

        auto begin_span = peek().span();
        SWALLOW(FN)
        auto function_scope = scope_tree->create_scope(scope.id);

        auto name = TRY(identifier(scope));


        EXPECT(LPAREN)

        auto params = TokenList{};

        while (!match(RPAREN)) {
            params.push_back(TRY(parameter(function_scope)));
        }

        EXPECT(RPAREN)


        EXPECT(ARROW)

        auto return_type = TRY(type());
        EXPECT(LCURLY)

        auto parsed_block = TRY(block(function_scope));

        EXPECT(RCURLY)
        auto end_span = peek().span();

        auto span = Span{begin_span.begin, end_span.end, begin_span.line, begin_span.col};

        auto fn = Function::create(
                std::move(params),
                std::move(parsed_block),
                *name,
                std::move(return_type),
                span
        );

        scope.functions[name->get()] = fn.get();
        return fn;
    }

    bool Parser::match(const Lexeme &match, int start) const noexcept {

        return peek(start) == match;
    }

    bool Parser::match(const LexemeType &match, int start) const noexcept {

        return peek(start).type() == match;
    }

    ErrorOr<Literal::Ptr> Parser::literal() {

        if (!match_any(Patterns::LiteralTypes))
            return fmt::format("Expected literal got {}", peek().to_string());

        advance();
        if (match(LexemeType::BOOLEAN_LITERAL, -1)) {

            return BooleanLiteral::create(peek(-1).data(), peek(-1).span());
        }
        if (match(LexemeType::NUMERIC_LITERAL, -1)) {
            return NumericLiteral::create(peek(-1).data(), peek(-1).span());
        }

        return StringLiteral::create(peek(-1).data(), peek(-1).span());

    }

    ErrorOr<FunctionCall::Ptr> Parser::function_call(Scope &scope, bool check_scope) {

        auto before_span = peek().span();
        auto name = TRY(identifier(scope));
        if (check_scope) {

            if (!scope.is_function_in_scope(name->get())) {

                return fmt::format(
                        "Function {} is not defined line {}, col {}",
                        name->get(),
                        name->span().line,
                        name->span().col
                );
            }
        }
        set_context(current_context().set_parsing_args(true));
        auto exprs = TRY(parse_multiple(scope, LPAREN, RPAREN));
        restore_context();
        auto after_span = peek(-1).span();
        auto span = Span{before_span.begin, after_span.end, before_span.line, before_span.col};
        return FunctionCall::create(name->get(), std::move(exprs), span);
    }

    Context Parser::current_context() {

        return context_stack.top();
    }

    void Parser::set_context(Context context) {

        context_stack.push(context);
    }

    void Parser::restore_context() {

        context_stack.pop();
    }

    ErrorOr<Expression::Ptr> Parser::return_expression(Scope &scope) {

        EXPECT(RETURN)
        set_context(current_context().set_parsing_return_expression(true));
        auto expr = TRY(parse_expression(scope));
        restore_context();
        EXPECT(SEMICOLON)
        return expr;
    }

    bool Parser::match_any(const Patterns::Pattern &matchers) const noexcept {

        for (const auto &matcher: matchers) {

            auto matched = std::visit(
                    Patterns::PatternVisitor{
                            [&, this](const Lexeme &lexeme) -> bool {
                                return peek() == lexeme;
                            },
                            [&, this](const LexemeType &lexeme_type) -> bool {
                                return peek().type() == lexeme_type;
                            }
                    }, matcher
            );
            if (matched)
                return true;

        }
        return false;
    }

    bool Parser::match(const Patterns::Pattern &matchers, int start) const noexcept {

        int lookahed = 0;
        for (std::size_t i = start; i < matchers.size(); ++i) {

            auto not_matched = std::visit(
                    Patterns::PatternVisitor{
                            [&, this](const Lexeme &lexeme) -> bool {
                                return peek(i + lookahed) != lexeme;
                            },
                            [&, this](const LexemeType &lexeme_type) -> bool {
                                return peek(i + lookahed).type() != lexeme_type;
                            }
                    }, matchers[i]
            );
            if (not_matched)
                return false;

        }
        return true;
    }

    ErrorOr<Assignment::Ptr> Parser::assignment(Scope &scope) {

        auto begin_span = peek().span();
        auto expr = TRY(parse_expression(scope));
        auto end_span = peek(-1).span();
        auto span = Span{begin_span.begin, end_span.end, begin_span.line, begin_span.col};
        EXPECT(SEMICOLON)
        return Assignment::create(std::move(expr), span);
    }


} // hasha
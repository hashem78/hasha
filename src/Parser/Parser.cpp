//
// Created by mythi on 21/07/22.
//

#include <fstream>

#include "magic_enum.hpp"

#include "Parser.h"
#include "Constants.h"

#define EXPECT(lexeme) if(!match(lexeme)) {return fmt::format("Expected {} Found {}",lexeme.to_string(),peek().to_string());}else{advance();}
#define EXPECT_NOT(l1) if(match(l1)) {return fmt::format("Unexpected {}",l1.to_string());}

#define SWALLOW(lexeme) if(match(lexeme)) {advance();}

namespace hasha {
    Parser::Parser(std::string file_name) : lexer(std::move(file_name)), cursor(0) {

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

        auto blk = TRY(block());

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


    const TokenList &Parser::get_tokens() const noexcept {

        return tokens;
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

    ErrorOr<Identifier::Ptr> Parser::identifier() noexcept {

        const auto name = peek().data();

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

        return Identifier::create(name, peek(-1).span());
    }

    ErrorOr<Type::Ptr> Parser::type() noexcept {

        auto type = peek().data();

        if (type.empty()) return "Failed to parse identifier name";

        if (std::isdigit(type[0])) return "An identifier cannot start with a digit";

        auto is_legal = [](char c) -> bool {
            return std::isalnum(c) || c == '_';
        };
        for (const auto &ch: type) {
            if (!is_legal(ch)) {
                return fmt::format("Illegal character {}", ch);
            }
        }

        advance();

        if (peek() == LBRACKET && peek(1) == RBRACKET) {
            advance(2);
            set_context(
                    current_context()
                            .set_parsing_array_type(true)
                            .set_parsing_value_type(false)
            );
            return ArrayType::create(type, peek(-2).span());
        }
        set_context(
                current_context()
                        .set_parsing_array_type(false)
                        .set_parsing_value_type(true)
        );
        return Type::create(type, peek(-1).span());
    }

    ErrorOr<Parameter::Ptr> Parser::parameter() {

        auto b_span = peek().span();
        auto param_type = TRY(type());
        auto name = TRY(identifier());

        if (match(COMMA)) advance();

        b_span.set_end(peek(-1).span().end);
        return Parameter::create(std::move(param_type), *name, b_span);
    }


    ErrorOr<Expression::Ptr> Parser::parse_expression(const Lexeme &delimiter) {

        std::deque<Lexeme> operators; // stack
        auto token_list = TokenList{};

        set_context(current_context().set_parsing_expression(true));

        auto begin_span = peek().span();

        while (!match(delimiter)) {
            auto x = peek();
            if (current_context().parsing_array && x == RBRACKET)
                break;
            if (current_context().parsing_array && x == COMMA)
                break;
            if (current_context().parsing_args && x == RPAREN)
                break;
            if (current_context().parsing_args && x == COMMA)
                break;

            advance();

            if (x.type() == LexemeType::IDENTIFIER) {
                advance(-1);
                token_list.push_back(TRY(function_call()));
            } else if (x.type() == LexemeType::OPERATOR) {
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

    ErrorOr<Assignment::Ptr> Parser::assignment() {

        EXPECT(EQUALS)

        Assignment::Ptr assignment;

        if (current_context().parsing_value_type) {
            EXPECT_NOT(LBRACKET)
            auto expr = TRY(parse_expression());
            auto span = expr->span();
            assignment = Assignment::create(std::move(expr), span);
        } else if (current_context().parsing_array_type) {
            set_context(current_context().set_parsing_array(true));
            auto before_span = peek().span();
            auto array_token_list = TRY(parse_multiple(LBRACKET, RBRACKET));
            auto after_span = peek(-1).span();
            auto span = Span{
                    before_span.begin,
                    after_span.end,
                    before_span.line,
                    before_span.col
            };
            restore_context();
            assignment = ArrayAssignment::create(std::move(array_token_list), span);

        }

        EXPECT(SEMICOLON)

        return assignment;
    }

    ErrorOr<ExpressionList>
    Parser::parse_multiple(const Lexeme &left, const Lexeme &right, const Lexeme &separator) {


        EXPECT(left)

        auto exprs = ExpressionList{};

        while (!match(right)) {
            SWALLOW(separator)
            exprs.push_back(TRY(parse_expression()));
        }
        EXPECT(right)

        return exprs;
    }

    ErrorOr<IfStatement::Ptr> Parser::if_statement() {

        auto span = peek().span();
        EXPECT(IF)
        auto condition = TRY(parse_expression(LCURLY));
        EXPECT(LCURLY)
        auto blk = TRY(block());
        EXPECT(RCURLY)

        return IfStatement::create(
                std::move(condition),
                std::move(blk),
                span
        );
    }

    ErrorOr<ElifStatement::Ptr> Parser::elif_statement() {

        if(!is_previous_of<IfStatement>() && !is_previous_of<ElifStatement>())
            return "Rouge elif statement";

        auto span = peek().span();
        EXPECT(ELIF)
        auto condition = TRY(parse_expression(LCURLY));
        EXPECT(LCURLY)
        auto blk = TRY(block());
        EXPECT(RCURLY)

        return ElifStatement::create(
                std::move(condition),
                std::move(blk),
                span
        );
    }

    ErrorOr<ElseStatement::Ptr> Parser::else_statement() {

        if(!is_previous_of<IfStatement>() && !is_previous_of<ElifStatement>())
            return "Rouge else statement";

        auto span = peek().span();
        EXPECT(ELSE)
        EXPECT(LCURLY)
        auto blk = TRY(block());
        EXPECT(RCURLY)

        return ElseStatement::create(std::move(blk), span);
    }

    ErrorOr<Declaration::Ptr> Parser::declaration() {

        auto before_span = peek().span();
        auto decl_type = TRY(type());
        auto name = TRY(identifier());

        if (peek() == EQUALS) {
            auto asx = TRY(assignment());

            auto after_span = peek(-1).span();

            auto span = Span{
                    before_span.begin,
                    after_span.end,
                    before_span.line,
                    before_span.col
            };

            return Declaration::create(
                    std::move(decl_type),
                    *name,
                    span,
                    std::move(asx)
            );
        }

        auto after_span = peek(-1).span();

        auto span = Span{
                before_span.begin,
                after_span.end,
                before_span.line,
                before_span.col
        };
        return Declaration::create(
                std::move(decl_type),
                *name,
                span
        );
    }

    ErrorOr<Block::Ptr> Parser::block() noexcept {

        auto token_list = TokenList{};
        auto begin_span = peek().span();
        while (!match(RCURLY)) {


            // Parse the unambigous statements first
            if (match(FN)) {
                token_list.push_back(TRY(function()));
            } else if (match(IF)) {
                token_list.push_back(TRY(if_statement()));
            } else if (match(ELSE)) {
                token_list.push_back(TRY(else_statement()));
            } else if (match(ELIF)) {
                token_list.push_back(TRY(elif_statement()));
            } else if (match(LexemeType::IDENTIFIER)) {
                token_list.push_back(TRY(declaration()));
            } else if (match(RETURN)) {
                token_list.push_back(TRY(return_expression()));
            } else {
                advance();
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

    ErrorOr<Function::Ptr> Parser::function() {

        auto begin_span = peek().span();
        SWALLOW(FN)

        auto name = TRY(identifier());

        EXPECT(LPAREN)

        auto params = TokenList{};

        while (!match(RPAREN)) {
            params.push_back(TRY(parameter()));
        }

        EXPECT(RPAREN)


        EXPECT(ARROW)

        auto return_type = TRY(type());
        EXPECT(LCURLY)

        auto parsed_block = TRY(block());

        EXPECT(RCURLY)
        auto end_span = peek().span();

        auto span = Span{begin_span.begin, end_span.end, begin_span.line, begin_span.col};

        return Function::create(
                std::move(params),
                std::move(parsed_block),
                *name,
                std::move(return_type),
                span
        );

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

    ErrorOr<FunctionCall::Ptr> Parser::function_call() {

        auto before_span = peek().span();
        auto name = TRY(identifier());
        set_context(current_context().set_parsing_args(true));
        auto exprs = TRY(parse_multiple(LPAREN, RPAREN));
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

    ErrorOr<Expression::Ptr> Parser::return_expression() {

        EXPECT(RETURN)
        set_context(current_context().set_parsing_return_expression(true));
        auto expr = TRY(parse_expression());
        restore_context();
        EXPECT(SEMICOLON)
        return expr;
    }

} // hasha
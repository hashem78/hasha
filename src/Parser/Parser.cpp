//
// Created by mythi on 21/07/22.
//

#include <fstream>

#include "magic_enum.hpp"

#include "Parser.h"
#include "Constants.h"
#include "Overload.h"
#include "Type/DefaultParserTypes.h"
#include "../TypeChecker/TypeChecker.h"

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

    ErrorOr<std::pair<Scope::Ptr, BoxedBlock>> Parser::parse() {

        auto global_scope = scope_tree->create_scope();
        return std::make_pair(global_scope, TRY(block(global_scope)));
    }


    ErrorOr<Box<Identifier>> Parser::identifier(const Scope::Ptr &scope) noexcept {

        const auto name = peek().data();

        if (name.empty()) return "Failed to parse name name";

        if (std::isdigit(name[0])) return "An name cannot start with a digit";

        auto is_legal = [](char c) -> bool {
            return std::isalnum(c) || c == '_';
        };
        for (const auto &ch: name) {
            if (!is_legal(ch)) {
                return fmt::format("Illegal character {}", ch);
            }
        }

        advance();

        return make_box<Identifier>(name, peek(-1).span(), scope->id);
    }

    ErrorOr<BoxedNormalType> Parser::type(const Scope::Ptr &scope) noexcept {

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

        advance();

        return make_box<NormalType>(type_name, peek(-1).span(), scope->id);
    }

    ErrorOr<BoxedGenericType> Parser::generic_type(const Scope::Ptr &scope) noexcept {

        auto generic = TRY(type(scope));
        auto before_span = peek().span();
        EXPECT(LANGEL)
        auto type_list = BoxedTypeList{};
        while (!match(RANGEL) && !match(SEMICOLON)) {
            SWALLOW(COMMA)
            type_list.push_back(TRY(type(scope)));
        }
        if (type_list.empty()) {
            return fmt::format(
                    "Generic Type {} with no type list, line: {}, col: {}",
                    generic->type(),
                    before_span.line,
                    before_span.col
            );
        }
        EXPECT(RANGEL)
        auto after_span = peek(-1).span();

        return make_box<GenericType>(
                generic,
                type_list,
                before_span.merge_with(after_span),
                scope->id
        );
    }

    ErrorOr<BoxedDeclaration> Parser::declaration(const Scope::Ptr &scope) noexcept {

        auto before_span = peek().span();
        auto name = TRY(identifier(scope));

        EXPECT(COLON)
        BoxedType decl_type;
        if (match(Patterns::GenericType))
            decl_type = TRY(generic_type(scope));
        else
            decl_type = TRY(type(scope));

        EXPECT(EQUALS)

        auto asx = TRY(parse_expression(scope));

        if (asx->empty()) {
            return fmt::format(
                    "Unintialized declaration of variable {} on line: {}, col: {}",
                    name->identifier(),
                    before_span.line,
                    before_span.col
            );
        }
        for (const auto &token: asx->expression()) {
            TRY(std::visit(
                    Overload{
                            [&name = name->identifier()](const BoxedIdentifier &var) -> ErrorOr<void> {

                                if (var->identifier() == name) {
                                    return fmt::format(
                                            "Tried to access {} before its declaration is compelete, on line: {}, col: {}",
                                            var->identifier(),
                                            var->span().line,
                                            var->span().col
                                    );
                                }
                                return {};
                            },
                            [](auto) -> ErrorOr<void> { return {}; }
                    },
                    token
            ));
        }

        auto checker = TypeChecker{decl_type, scope};
        TRY(checker.check_expression(asx));

        auto after_span = peek(-1).span();

        auto span = Span{
                before_span.begin,
                after_span.end,
                before_span.line,
                before_span.col
        };

        auto declaration = make_box<Declaration>(
                decl_type,
                name,
                asx,
                span,
                scope->id
        );
        scope->declarations[name->identifier()] = declaration;
        return declaration;
    }

    ErrorOr<Box<Expression>> Parser::parse_expression(
            const Scope::Ptr &scope,
            const Lexeme &delimiter
    ) {


        std::deque <Lexeme> operators; // stack
        auto token_list = TokenList{};

        set_context(current_context().set_parsing_expression(true));


        auto begin_span = peek().span();


        auto push_operator = [&scope, &token_list](const Lexeme &lexeme) {
            token_list.push_back(
                    make_box<Operator>(
                            lexeme.operator_type(),
                            lexeme.data(),
                            lexeme.span(),
                            scope->id
                    )
            );
        };

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

                        push_operator(y);

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
                    push_operator(operators.front());
                    operators.pop_front();
                }
                // TODO: If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                if (operators.front() != LPAREN)
                    break;
                operators.pop_front();
            } else {
                if (x != COMMA) {
                    switch (x.type()) {
                        case LexemeType::LITERAL: {
                            advance(-1);
                            token_list.push_back(TRY(literal(scope)));
                        }
                            break;
                        case LexemeType::IDENTIFIER: {
                            advance(-1);
                            auto idn = TRY(identifier(scope));
                            if (!scope->is_declaration_in_scope(idn->identifier())) {
                                return fmt::format(
                                        "Identifier {} is undefined in this scope, line: {}, col {}",
                                        idn->identifier(),
                                        idn->span().line,
                                        idn->span().col
                                );
                            }
                            token_list.push_back(idn);
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
            push_operator(operators.front());
            operators.pop_front();
        }

        restore_context();
        auto end_span = peek(-1).span();

        return make_box<Expression>(
                token_list,
                begin_span.merge_with(end_span),
                scope->id
        );
    }

    ErrorOr<BoxedFunctionCall>
    Parser::function_call(
            const Scope::Ptr &scope,
            bool check_scope
    ) noexcept {

        auto before_span = peek().span();
        auto idn = TRY(identifier(scope));
        if (check_scope) {

            if (!scope->is_function_in_scope(idn->identifier())) {

                return fmt::format(
                        "Function {} is not defined line {}, col {}",
                        idn->identifier(),
                        idn->span().line,
                        idn->span().col
                );
            }
        }
        set_context(current_context().set_parsing_args(true));
        auto exprs = TRY(parse_multiple(scope, LPAREN, RPAREN));
        restore_context();
        auto after_span = peek(-1).span();

        return make_box<FunctionCall>(
                idn->identifier(),
                exprs,
                before_span.merge_with(after_span),
                scope->id
        );
    }

    ErrorOr<BoxedExpressionList>
    Parser::parse_multiple(
            const Scope::Ptr &scope,
            const Lexeme &left,
            const Lexeme &right,
            const Lexeme &separator
    ) {

        EXPECT(left)

        auto exprs = BoxedExpressionList{};

        while (!match(right)) {
            SWALLOW(separator)
            exprs.push_back(TRY(parse_expression(scope)));
        }
        EXPECT(right)

        return exprs;
    }

    ErrorOr<BoxedLiteral> Parser::literal(const Scope::Ptr &scope) noexcept {


        if (!match(LexemeType::LITERAL))
            return fmt::format("Expected literal got {}", peek().to_string());

        advance();
        return  make_box<Literal>(peek(-1).litreal_type(), peek(-1).data(), peek(-1).span(), scope->id);
    }

    ErrorOr<BoxedBlock> Parser::block(const Scope::Ptr &scope) noexcept {

        auto token_list = TokenList{};
        auto begin_span = peek().span();
        bool found_return = false;

        while (!match(RCURLY) && !match(EOFL)) {

            // Parse the unambigous statements first
            if (match(FN)) {
                token_list.push_back(TRY(function(scope)));
            } else if (match(IF)) {
                token_list.push_back(TRY(if_statement(scope)));
            } else if (match(ELSE)) {
                // FIXME: Rouge else statements at the start of a block cause access problems
                token_list.push_back(TRY(else_statement(token_list.back(), scope)));
            } else if (match(ELIF)) {
                // FIXME: Rouge elif statements at the start of a block cause access problems
                token_list.push_back(TRY(elif_statement(token_list.back(), scope)));
            } else if (match(Patterns::Declaration)) {
                token_list.push_back(TRY(declaration(scope)));
                EXPECT(SEMICOLON)
            } else if (match(Patterns::Assignment)) {
                token_list.push_back(TRY(assignment(scope)));
            } else if (match(RETURN)) {
                token_list.push_back(TRY(return_token(scope)));
                found_return = true;
            } else {
                token_list.push_back(TRY(parse_expression(scope)));
                EXPECT(SEMICOLON)
            }
        }
        auto end_span = peek().span();

        return make_box<Block>(
                token_list,
                begin_span.merge_with(end_span),
                scope->id,
                found_return
        );

    }

    ErrorOr<BoxedParameter> Parser::parameter(const Scope::Ptr &scope) noexcept {

        auto before_span = peek().span();
        auto name = TRY(identifier(scope));
        EXPECT(COLON)
        auto param_type = TRY(type(scope));

        auto after_span = peek().span();

        return make_box<Parameter>(
                param_type,
                name,
                before_span.merge_with(after_span),
                scope->id
        );
    }

    ErrorOr<BoxedFunction> Parser::function(const Scope::Ptr &scope) noexcept {

        auto begin_span = peek().span();
        SWALLOW(FN)
        auto function_scope = scope_tree->create_scope(scope->id);

        auto name = TRY(identifier(scope));


        EXPECT(LPAREN)

        auto params = BoxedParameterList{};


        while (!match(RPAREN)) {
            SWALLOW(COMMA)
            params.push_back(TRY(parameter(function_scope)));
        }

        for (const auto &parameter: params) {
            function_scope->parameters[parameter->name()->identifier()] = parameter;
        }

        EXPECT(RPAREN)


        EXPECT(ARROW)

        if (match(Patterns::GenericType)) {
            auto return_type = TRY(generic_type(scope));

            EXPECT(LCURLY)

            auto parsed_block = TRY(block(function_scope));

            if (!parsed_block->contains_return()) {
                fmt::print(
                        "Non-void function {} does not return anything on line: {}, col: {}",
                        name->identifier(),
                        name->span().line,
                        name->span().col
                );
            } else {
                auto checker = TypeChecker{return_type, function_scope};
                for (const auto &token: parsed_block->tokens()) {
                    if (std::holds_alternative<BoxedReturnToken>(token)) {
                        const auto &return_token = std::get<BoxedReturnToken>(token);
                        TRY(checker.check_expression(return_token->expression()));
                    }
                }
            }

            EXPECT(RCURLY)
            auto end_span = peek().span();

            auto fn = make_box<Function>(
                    name,
                    params,
                    return_type,
                    parsed_block,
                    begin_span.merge_with(end_span),
                    scope->id
            );

            scope->functions[name->identifier()] = fn;
            return fn;
        } else {
            auto return_type = TRY(type(scope));

            auto return_type_is_void = *return_type == *DefVoidType;

            if (return_type_is_void) {
                set_context(current_context().set_parsing_void_function(true));
            }

            EXPECT(LCURLY)

            auto parsed_block = TRY(block(function_scope));

            if (return_type_is_void) {
                restore_context();
            }

            if (!return_type_is_void && !parsed_block->contains_return()) {
                fmt::print(
                        "Non-void function {} does not return anything on line: {}, col: {}",
                        name->identifier(),
                        name->span().line,
                        name->span().col
                );
            } else {
                auto checker = TypeChecker{return_type, function_scope};
                for (const auto &token: parsed_block->tokens()) {
                    if (std::holds_alternative<BoxedReturnToken>(token)) {
                        const auto &return_token = std::get<BoxedReturnToken>(token);
                        TRY(checker.check_expression(return_token->expression()));
                    }
                }
            }

            EXPECT(RCURLY)
            auto end_span = peek().span();

            auto fn = make_box<Function>(
                    name,
                    params,
                    return_type,
                    parsed_block,
                    begin_span.merge_with(end_span),
                    scope->id
            );

            scope->functions[name->identifier()] = fn;
            return fn;
        }
    }

    ErrorOr<BoxedAssignment> Parser::assignment(const Scope::Ptr &scope) noexcept {

        auto begin_span = peek().span();
        auto idn = TRY(identifier(scope));

        if (!scope->is_declaration_in_scope(idn->identifier())) {
            return fmt::format(
                    "{} is not declared in this scope on line: {}, col: {}",
                    idn->identifier(),
                    idn->span().line,
                    idn->span().col
            );
        }
        EXPECT(EQUALS)
        auto expr = TRY(parse_expression(scope));
        auto declaration = scope->get_declaration(idn->identifier());
        auto checker = TypeChecker{declaration->type(), scope};
        TRY(checker.check_expression(expr));
        auto end_span = peek(-1).span();
        EXPECT(SEMICOLON)

        return make_box<Assignment>(
                idn,
                expr,
                begin_span.merge_with(end_span),
                scope->id
        );
    }

    ErrorOr<BoxedIfStatement> Parser::if_statement(const Scope::Ptr &scope) noexcept {

        auto before_span = peek().span();
        EXPECT(IF)
        auto condition = TRY(parse_expression(scope, LCURLY));
        auto checker = TypeChecker{DefBooleanType, scope};
        TRY(checker.check_expression(condition));
        EXPECT(LCURLY)
        auto blk = TRY(block(scope_tree->create_scope(scope->id)));
        EXPECT(RCURLY)
        auto after_span = peek(-1).span();

        return make_box<IfStatement>(
                condition,
                blk,
                before_span.merge_with(after_span),
                scope->id
        );
    }

    ErrorOr<BoxedElifStatement> Parser::elif_statement(
            const Token &previous_token,
            const Scope::Ptr &scope
    ) noexcept {

        auto previous_is_if = std::holds_alternative<BoxedIfStatement>(previous_token);
        auto previous_is_else = std::holds_alternative<BoxedElseStatement>(previous_token);
        auto previous_is_elif = std::holds_alternative<BoxedIfStatement>(previous_token);

        if (!previous_is_if && !previous_is_elif) {
            return fmt::format(
                    "elif statement has to be preceeded by either if or elif statments on line: {}, col: {}",
                    peek().span().line,
                    peek().span().col
            );
        }

        if (previous_is_else) {
            return fmt::format(
                    "elif statement cannot to be preceeded by else statment on line: {}, col: {}",
                    peek().span().line,
                    peek().span().col
            );
        }

        auto before_span = peek().span();
        EXPECT(ELIF)
        auto condition = TRY(parse_expression(scope, LCURLY));
        auto checker = TypeChecker{DefBooleanType, scope};
        TRY(checker.check_expression(condition));
        EXPECT(LCURLY)
        auto blk = TRY(block(scope_tree->create_scope(scope->id)));
        EXPECT(RCURLY)
        auto after_span = peek(-1).span();

        return make_box<ElifStatement>(
                condition,
                blk,
                before_span.merge_with(after_span),
                scope->id
        );
    }

    ErrorOr<BoxedElseStatement> Parser::else_statement(
            const Token &previous_token,
            const Scope::Ptr &scope
    ) noexcept {

        auto previous_is_if = std::holds_alternative<BoxedIfStatement>(previous_token);
        auto previous_is_elif = std::holds_alternative<BoxedIfStatement>(previous_token);

        if (!previous_is_if && !previous_is_elif) {
            return fmt::format(
                    "else statement has to be preceeded by either if or else statments on line: {}, col: {}",
                    peek().span().line,
                    peek().span().col
            );
        }

        auto before_span = peek().span();
        EXPECT(ELSE)
        EXPECT(LCURLY)
        auto blk = TRY(block(scope_tree->create_scope(scope->id)));
        EXPECT(RCURLY)
        auto after_span = peek(-1).span();

        return make_box<ElseStatement>(
                blk,
                before_span.merge_with(after_span),
                scope->id
        );
    }

    ErrorOr<BoxedReturnToken> Parser::return_token(const Scope::Ptr &scope) noexcept {

        auto begin_span = peek().span();
        EXPECT(RETURN);
        auto ret = TRY(parse_expression(scope));

        if (current_context().parsing_void_function) {
            if (!ret->expression().empty()) {
                return fmt::format(
                        "Expected empty return expression on line: {}, col: {} ",
                        ret->span().line,
                        ret->span().col
                );
            }
        } else {
            if (ret->expression().empty()) {
                return fmt::format(
                        "Expected non-empty return expression on line: {}, col: {} ",
                        ret->span().line,
                        ret->span().col
                );
            }
        }
        auto end_span = peek().span();

        return make_box<ReturnToken>(
                ret,
                begin_span.merge_with(end_span),
                scope->id
        );
    }

    bool Parser::match(const Lexeme &match, int start) const noexcept {

        return peek(start) == match;
    }

    bool Parser::match(const LexemeType &match, int start) const noexcept {

        return peek(start).type() == match;
    }

    bool Parser::match(const Patterns::Pattern &matchers) const noexcept {

        int lookahed = 0;
        for (std::size_t i = 0; i < matchers.size(); ++i) {

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

    Context Parser::current_context() {

        return context_stack.top();
    }

    void Parser::set_context(Context context) {

        context_stack.push(context);
    }

    void Parser::restore_context() {

        context_stack.pop();
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


} // hasha
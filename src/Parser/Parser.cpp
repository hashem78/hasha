//
// Created by mythi on 21/07/22.
//

#include "Parser.h"

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

    void Parser::parse() {

        auto blk = block();
        if (blk.is_error())
            fmt::print("{}\n", blk.error());
        else {
            fmt::print("{}\n", blk.value()->to_string());
        }

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

        return Identifier::create(name);
    }

    ErrorOr<Type::Ptr> Parser::type() noexcept {

        auto name = TRY(identifier());

        if (peek() == LBRACKET && peek(1) == RBRACKET) {
            advance();
            advance();
            set_context(
                    current_context()
                            .set_parsing_array_type(true)
                            .set_parsing_value_type(false)
            );
            return ArrayType::create(*name);
        }
        set_context(
                current_context()
                        .set_parsing_array_type(false)
                        .set_parsing_value_type(true)
        );
        return Type::create(*name);
    }

    ErrorOr<Parameter::Ptr> Parser::parameter() {

        auto param_type = TRY(type());
        auto name = TRY(identifier());

        if (match(COMMA)) advance();

        return Parameter::create(std::move(param_type), *name);
    }


    ErrorOr<Expression::Ptr> Parser::parse_expression(const Lexeme &delimiter) {

        std::deque<Lexeme> output; // queue
        std::deque<Lexeme> operators; // stack
        auto token_list = create_token_list();

        set_context(current_context().set_parsing_expression(true));

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
                token_list->push_back(TRY(function_call()));
            } else if (x.type() == LexemeType::OPERATOR) {
                while (!operators.empty() && operators.front().type() == LexemeType::OPERATOR) {
                    auto y = operators.front();

                    if ((x.associativity() == Associativity::LEFT &&
                         x.precedence() <= y.precedence()) ||
                        (x.associativity() == Associativity::RIGHT &&
                         x.precedence() < y.precedence())) {

                        token_list->push_back(Operator::create(y.data()));
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
                    token_list->push_back(Operator::create(operators.front().data()));
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
                            token_list->push_back(NumericLiteral::create(x.data()));
                            break;
                        case LexemeType::STRING_LITERAL:
                            token_list->push_back(StringLiteral::create(x.data()));
                            break;
                        case LexemeType::BOOLEAN_LITERAL:
                            token_list->push_back(BooleanLiteral::create(x.data()));
                            break;
                        default:
                            return fmt::format("Unknown token {} in expression\n", x.to_string());
                    }
                    output.push_back(x);
                }
            }
        }

        while (!operators.empty()) {
            token_list->push_back(Operator::create(operators.front().data()));
            operators.pop_front();
        }

        restore_context();
        return Expression::create(token_list);

    }

    ErrorOr<Assignment::Ptr> Parser::assignment() {

        EXPECT(EQUALS)

        Assignment::Ptr assignment;
        if (current_context().parsing_value_type) {
            EXPECT_NOT(LBRACKET)

            assignment = Assignment::create(TRY(parse_expression()));
        } else if (current_context().parsing_array_type) {
            set_context(current_context().set_parsing_array(true));
            auto array_token_list = TRY(parse_multiple(LBRACKET, RBRACKET));
            restore_context();
            assignment = ArrayAssignment::create(std::move(array_token_list));

        }

        EXPECT(SEMICOLON)

        return assignment;
    }

    ErrorOr<ExpressionListPtr>
    Parser::parse_multiple(const Lexeme &left, const Lexeme &right, const Lexeme &separator) {


        EXPECT(left)

        auto exprs = create_expression_list();

        while (!match(right)) {
            SWALLOW(separator)
            exprs->push_back(TRY(parse_expression()));
        }
        EXPECT(right)

        return exprs;
    }

    ErrorOr<IfStatement::Ptr> Parser::if_statement() {

        EXPECT(IF)
        auto condition = TRY(parse_expression(LCURLY));
        EXPECT(LCURLY)
        auto blk = TRY(block());
        EXPECT(RCURLY)

        return IfStatement::create(std::move(condition), std::move(blk));
    }

    ErrorOr<ElifStatement::Ptr> Parser::elif_statement() {

        EXPECT(ELIF)
        auto condition = TRY(parse_expression(LCURLY));
        EXPECT(LCURLY)
        auto blk = TRY(block());
        EXPECT(RCURLY)

        return ElifStatement::create(std::move(condition), std::move(blk));
    }

    ErrorOr<ElseStatement::Ptr> Parser::else_statement() {

        EXPECT(ELSE)
        EXPECT(LCURLY)
        auto blk = TRY(block());
        EXPECT(RCURLY)

        return ElseStatement::create(std::move(blk));
    }

    ErrorOr<Declaration::Ptr> Parser::declaration() {

        auto decl_type = TRY(type());
        auto name = TRY(identifier());

        if (peek() == EQUALS) {

            return Declaration::create(
                    std::move(decl_type),
                    *name,
                    TRY(assignment())
            );
        }
        return Declaration::create(
                std::move(decl_type),
                *name
        );
    }

    ErrorOr<Block::Ptr> Parser::block() noexcept {

        auto token_list = create_token_list();
        while (!match(RCURLY)) {

            // In a return function block there is going to be a
            // return keyword.
            if (match(RETURN)) {
                return Block::create(token_list);
            }

            // Parse the unambigous statements first
            if (match(FN)) {
                token_list->push_back(TRY(function()));
            } else if (match(IF)) {
                token_list->push_back(TRY(if_statement()));
            } else if (match(ELSE)) {
                token_list->push_back(TRY(else_statement()));
            } else if (match(ELIF)) {
                token_list->push_back(TRY(elif_statement()));
            } else if (match(LexemeType::IDENTIFIER)) {
                token_list->push_back(TRY(declaration()));
            } else {
                advance();
            }
        }

        return Block::create(token_list);
    }

    ErrorOr<Function::Ptr> Parser::function() {

        SWALLOW(FN)

        auto name = TRY(identifier());

        EXPECT(LPAREN)

        auto params = create_token_list();

        while (!match(RPAREN)) {
            params->push_back(TRY(parameter()));
        }

        EXPECT(RPAREN)


        EXPECT(ARROW)

        auto return_type = TRY(type());
        EXPECT(LCURLY)

        auto parsed_block = TRY(block());

        EXPECT(RETURN)
        auto return_expression = TRY(parse_expression());

        EXPECT(SEMICOLON)
        EXPECT(RCURLY)

        return Function::create(
                std::move(params),
                std::move(parsed_block),
                *name,
                std::move(return_type),
                std::move(return_expression)
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

            return BooleanLiteral::create(peek(-1).data());
        }
        if (match(LexemeType::NUMERIC_LITERAL, -1)) {
            return NumericLiteral::create(peek(-1).data());
        }

        return StringLiteral::create(peek(-1).data());

    }

    ErrorOr<FunctionCall::Ptr> Parser::function_call() {

        auto name = TRY(identifier());
        set_context(current_context().set_parsing_args(true));
        auto exprs = TRY(parse_multiple(LPAREN, RPAREN));
        restore_context();
        return FunctionCall::create(name->get(), std::move(exprs));
    }

} // hasha
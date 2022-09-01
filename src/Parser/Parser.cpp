//
// Created by mythi on 21/07/22.
//

#include "Parser.h"

#define EXPECT(lexeme) if(!match(lexeme)) {return fmt::format("Expected {} Found {}",lexeme.to_string(),peek().to_string());}else{advance();}


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

    bool Parser::done() const noexcept {

        if (cursor >= lexemes.size())
            return true;

        return false;
    }

    Lexeme Parser::advance() noexcept {

        if (!done())
            return lexemes[cursor++];

        return lexemes.back();
    }

    ErrorOr<Identifier> Parser::identifier() noexcept {

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

        return Identifier{name};
    }

    ErrorOr<Type::Ptr> Parser::type() noexcept {

        auto name = TRY(identifier());

        if (peek() == LBRACKET && peek(1) == RBRACKET) {
            advance();
            advance();
            return ArrayType::create(name);
        }

        return Type::create(name);
    }

    ErrorOr<Parameter::Ptr> Parser::parameter() {

        auto param_type = TRY(type());
        auto name = TRY(identifier());

        if (match(COMMA)) advance();

        return Parameter::create(std::move(param_type), name);
    }

    ErrorOr<Declaration::Ptr> Parser::variable_declaration() {

        auto var_type = TRY(type());
        auto name = TRY(identifier());

        EXPECT(SEMICOLON)

        return Declaration::create(std::move(var_type), name);
    }


    ErrorOr<TokenListPtr> Parser::parse_expression(const Lexeme &delimiter) {

        std::deque<Lexeme> output; // queue
        std::deque<Lexeme> operators; // stack


        while (!match(delimiter)) {
            auto x = peek();
            advance();

            if (x.type() == LexemeType::IDENTIFIER) {
                operators.push_front(x);
            } else if (x.type() == LexemeType::OPERATOR) {
                while (!operators.empty() && operators.front().type() == LexemeType::OPERATOR) {
                    auto y = operators.front();

                    if ((x.associativity() == Associativity::LEFT &&
                         x.precedence() <= y.precedence()) ||
                        (x.associativity() == Associativity::RIGHT &&
                         x.precedence() < y.precedence())) {
                        output.push_back(y);
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
                    output.push_back(operators.front());
                    operators.pop_front();
                }
                // TODO: If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                if (operators.front() != LPAREN)
                    break;
                operators.pop_front();
                if (operators.front().type() == LexemeType::IDENTIFIER) {
                    output.push_back(operators.front());
                    operators.pop_front();
                }
            } else {
                if (x != COMMA) {
                    output.push_back(x);
                }
            }
        }

        while (!operators.empty()) {
            output.push_back(operators.front());
            operators.pop_front();
        }

        auto token_list = create_token_list();


        for (auto &out_tok: output) {
            fmt::print("{} ", out_tok.data());
            switch (out_tok.type()) {
                case LexemeType::OPERATOR:
                    token_list->push_back(Operator::create(out_tok.data()));
                    break;
                case LexemeType::NUMERIC_LITERAL:
                    token_list->push_back(NumericLiteral::create(out_tok.data()));
                    break;
                case LexemeType::STRING_LITERAL:
                    token_list->push_back(StringLiteral::create(out_tok.data()));
                    break;
                case LexemeType::BOOLEAN_LITERAL:
                    token_list->push_back(BooleanLiteral::create(out_tok.data()));
                    break;

                case LexemeType::IDENTIFIER:
                    token_list->push_back(Identifier::create(out_tok.data()));
                    break;

                default:
                    return fmt::format("Unknown token {} in expression\n", out_tok.to_string());
            }
        }
        fmt::print("\n");
        return token_list;

    }

    ErrorOr<Declaration::Ptr> Parser::variable_declaration_and_assignment() {

        auto var_type = TRY(type());
        auto name = TRY(identifier());

        EXPECT(EQUALS)

        auto token_list = TRY(parse_expression());

        EXPECT(SEMICOLON)

        return Declaration::create(
                std::move(var_type),
                name,
                Assignment::create(name, token_list)
        );
    }

    ErrorOr<Declaration::Ptr> Parser::array_declaration_and_assignemnt() {

        auto arr_type = TRY(type());

        auto name = TRY(identifier());

        EXPECT(EQUALS)

        auto token_list = TRY(parse_multiple(LBRACKET, RBRACKET));

        return Declaration::create(
                std::move(arr_type),
                name,
                Assignment::create(name, token_list)
        );
    }

    ErrorOr<Assignment::Ptr> Parser::variable_assignment() {

        auto name = TRY(identifier());
        EXPECT(EQUALS)

        Assignment::Ptr assignment;

        if (match(LBRACKET)) {
            auto array_token_list = TRY(parse_multiple(LBRACKET, RBRACKET));


            assignment = Assignment::create(name, array_token_list, true);

        } else {
            auto expression_token_list = TRY(parse_expression());

            assignment = Assignment::create(name, expression_token_list);
        }

        EXPECT(SEMICOLON)

        return assignment;
    }

    ErrorOr<TokenListPtr>
    Parser::parse_multiple(const Lexeme &left, const Lexeme &right, const Lexeme &separator) {

        EXPECT(left)

        auto token_list = create_token_list();

        while (!match(right)) {
            SWALLOW(COMMA)
            if (match(LexemeType::LITERAL)) {
                auto ltrl = peek();

                switch (ltrl.type()) {
                    case LexemeType::STRING_LITERAL:
                        token_list->push_back(StringLiteral::create(ltrl.data()));
                        break;
                    case LexemeType::BOOLEAN_LITERAL:
                        token_list->push_back(BooleanLiteral::create(ltrl.data()));
                        break;
                    case LexemeType::NUMERIC_LITERAL:
                        token_list->push_back(NumericLiteral::create(ltrl.data()));
                        break;
                    default:
                        break;
                }
                advance();
            } else {
                auto expression = TRY(parse_expression());

                token_list->insert(
                        token_list->end(),
                        std::make_move_iterator(expression->begin()),
                        std::make_move_iterator(expression->end())
                );
            }
        }
        EXPECT(right)
        return token_list;
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

    ErrorOr<Block::Ptr> Parser::block() noexcept {

        auto token_list = create_token_list();
        while (!match(RCURLY)) {

            // In a return function block there is going to be a
            // return keyword.
            if (match(RETURN)) {
                return Block::create(token_list);
            }
            if (match(Patterns::IfStatement)) {

                token_list->push_back(TRY(if_statement()));

            } else if (match(Patterns::ElifStatement)) {

                if (is_previous_of<ElseStatement>(token_list.get())) {
                    return "elif following else statement";
                }
                if (!is_previous_of<IfStatement>(token_list.get())) {
                    return "Rouge elif block";
                }
                token_list->push_back(TRY(elif_statement()));

            } else if (match(Patterns::ElseStatement)) {

                if (!is_previous_of<IfStatement>(token_list.get())) {
                    return "Rouge else block";
                }
                token_list->push_back(TRY(else_statement()));

            } else if (match(Patterns::FunctionDefinition)) {

                token_list->push_back(TRY(function()));

            } else if (match(Patterns::VariableAssignment)) {

                token_list->push_back(TRY(variable_assignment()));

            } else if (match(Patterns::VariableDeclaration)) {

                token_list->push_back(TRY(variable_declaration()));

            } else if (match(Patterns::ArrayDeclaration)) {

                token_list->push_back(TRY(variable_declaration()));

            } else if (match(Patterns::VariableDeclarationAndAssignment)) {

                token_list->push_back(TRY(variable_declaration_and_assignment()));

            } else if (match(Patterns::ArrayDeclarationAndAssignment)) {

                token_list->push_back(TRY(array_declaration_and_assignemnt()));

            } else if (match(Patterns::FunctionCall)) {

                auto fn_call = TRY(parse_expression());
                token_list->push_back(FunctionCall::create(fn_call->back()->to_string(), fn_call));

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
                name,
                std::move(return_type),
                std::move(return_expression)
        );

    }

    bool Parser::match(const Lexeme &match) const noexcept {

        if (peek() == match) {
            return true;
        }
        return false;
    }

    bool Parser::match(const LexemeType &match) const noexcept {

        if (peek().type() == match) {
            return true;
        }
        return false;
    }


} // hasha
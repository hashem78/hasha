//
// Created by mythi on 21/07/22.
//

#include <thread>
#include <utility>
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

        const auto name = peek().get_data();

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

    ErrorOr<Parameter::Ptr> Parser::parameter() {

        auto type = TRY(identifier());
        auto name = TRY(identifier());

        if (match(COMMA)) advance();

        return Parameter::create(name, type);
    }

    ErrorOr<Declaration::Ptr> Parser::variable_declaration() {

        auto type = TRY(identifier());
        auto name = TRY(identifier());

        EXPECT(SEMICOLON)

        return Declaration::create(type, name);
    }

    ErrorOr<Declaration::Ptr> Parser::array_declaration() {

        auto type = TRY(identifier());
        EXPECT(LBRACKET)
        EXPECT(RBRACKET)

        auto name = TRY(identifier());

        return Declaration::create(type, name, nullptr, true);
    }

    ErrorOr<Declaration::Ptr> Parser::array_declaration_and_assignemnt() {

        auto type = TRY(identifier());

        EXPECT(LBRACKET)
        EXPECT(RBRACKET)

        auto name = TRY(identifier());

        EXPECT(EQUALS)

        auto token_list = TRY(parse_multiple(LBRACKET, RBRACKET));

        auto assignment = Assignment::create(name, token_list, true);
        return Declaration::create(type, name, std::move(assignment), true);
    }

    ErrorOr<TokenListPtr> Parser::parse_expression() {

        std::deque<Lexeme> output; // queue
        std::deque<Lexeme> operators; // stack


        while (!match(SEMICOLON)) {
            auto x = peek();
            advance();

            if (x.get_type() == LexemeType::IDENTIFIER) {
                operators.push_front(x);
            } else if (x.get_type() == LexemeType::OPERATOR) {

                while (!operators.empty() && operators.front().get_type() == LexemeType::OPERATOR) {
                    auto y = operators.front();

                    if ((x.get_associativity() == Associativity::Left &&
                         x.get_precedence() <= y.get_precedence()) ||
                        (x.get_associativity() == Associativity::Right &&
                         x.get_precedence() < y.get_precedence())) {
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
                if (operators.front().get_type() == LexemeType::IDENTIFIER) {
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
            switch (out_tok.get_type()) {

                case OPERATOR: {
                    if (out_tok.is_boolean_operator()) {

                        token_list->push_back(BooleanOperator::create(out_tok.get_data()));
                    } else {

                        token_list->push_back(NumericOperator::create(out_tok.get_data()));
                    }
                    break;
                }
                case LITERAL: {
                    if (out_tok.is_string()) {
                        token_list->push_back(StringLiteral::create(out_tok.get_data()));
                    } else {
                        token_list->push_back(NumericLiteral::create(out_tok.get_data()));
                    }
                    break;
                }
                case KEYWORD: {
                    if (out_tok.is_boolean()) {
                        token_list->push_back(BooleanLiteral::create(out_tok.get_data()));
                    }
                    break;
                }
                case IDENTIFIER: {

                    token_list->push_back(Identifier::create(out_tok.get_data()));

                    break;
                }
                default:
                    return fmt::format("Unknown token {} in expression\n", out_tok.to_string());
            }
        }

        return token_list;

    }

    ErrorOr<Declaration::Ptr> Parser::variable_declaration_and_assignment() {

        auto type = TRY(identifier());
        auto name = TRY(identifier());

        EXPECT(EQUALS)

        auto token_list = TRY(parse_expression());

        EXPECT(SEMICOLON)
        return Declaration::create(type, name, Assignment::create(name, token_list));
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

    ErrorOr<TokenListPtr> Parser::parse_multiple(const Lexeme &left, const Lexeme &right, const Lexeme &separator) {

        EXPECT(left)

        auto token_list = create_token_list();

        while (!match(right)) {
            if (match(LexemeType::LITERAL)) {
                auto ltrl = peek();
                SWALLOW(separator)

                if (ltrl.is_string()) {
                    token_list->push_back(StringLiteral::create(ltrl.get_data()));
                } else if (ltrl.is_boolean()) {
                    token_list->push_back(BooleanLiteral::create(ltrl.get_data()));
                } else {
                    token_list->push_back(NumericLiteral::create(ltrl.get_data()));
                }
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

    ErrorOr<Block::Ptr> Parser::block() noexcept {

        auto token_list = create_token_list();
        while (!match(RCURLY)) {

            // In a return function block there is going to be a
            // return keyword.
            if (match(RETURN)) {
                return Block::create(token_list);
            }
            if (match(Patterns::FunctionDefinition)) {
                fmt::print("PARSING FUNCTION\n");
                token_list->push_back(TRY(function()));
            } else if (match(Patterns::VariableAssignment)) {
                token_list->push_back(TRY(variable_assignment()));
            } else if (match(Patterns::VariableDeclaration)) {
                token_list->push_back(TRY(variable_declaration()));
            } else if (match(Patterns::VariableDeclarationAndAssignment)) {
                token_list->push_back(TRY(variable_declaration_and_assignment()));
            } else if (match(Patterns::ArrayDeclaration)) {
                token_list->push_back(TRY(array_declaration()));
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

        auto return_type = TRY(identifier());
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

        if (peek().get_type() == match) {
            return true;
        }
        return false;
    }


} // hasha
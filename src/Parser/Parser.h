//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_PARSER_H
#define HASHA_PARSER_H

#include <optional>
#include <variant>
#include <deque>
#include <thread>

#include "magic_enum.hpp"

#include "Tokens/Token.h"
#include "Lexeme.h"
#include "Identifier.h"
#include "Lexer.h"
#include "Parameter.h"
#include "Function.h"
#include "Literal.h"
#include "Tokens/Declaration.h"
#include "Operator.h"
#include "Pattern.h"

#define VERIFY(var) if (holds_alternative<ParseError>(var)) {return get<ParseError>(var);}
#define EXPECT(lexeme) if(!match(lexeme)) {return fmt::format("Expected {} Found {}",lexeme.to_string(),peek().to_string());}else{advance();}
#define EXPECT_TYPE(lexemeType) if(!match(lexemeType)) {return fmt::format("Expected {} Found {}",magic_enum::enum_name(lexemeType),peek().to_string());}else{advance();}

namespace hasha {
    using ParseError = std::string;
    template<typename Token= TokenPtr, typename Err = ParseError>
    using ErrorOr = std::variant<Token, Err>;

    class Parser {
        Lexer lexer;
        LexemeList lexemes;
        int cursor;

        TokenList tokens;

        [[nodiscard]]
        Lexeme peek(std::size_t k = 0) const noexcept;

        [[nodiscard]]
        bool done() const noexcept {

            if (cursor >= lexemes.size())
                return true;

            return false;
        }

        Lexeme advance() noexcept {

            if (!done())
                return lexemes[cursor++];

            return lexemes.back();
        }

        [[nodiscard]]
        inline bool match(const Lexeme &match) const noexcept {

            if (peek() == match) {
                return true;
            }
            return false;
        }

        [[nodiscard]]
        inline bool match(const LexemeType &match) const noexcept {

            if (peek().get_type() == match) {
                return true;
            }
            return false;
        }

        template<size_t S>
        inline bool match(const Patterns::Pattern<S> &matchers) const noexcept {

            for (std::size_t i = 0; i < matchers.size(); ++i) {

                auto matcher = matchers[i];

                if (holds_alternative<LexemeType>(matcher)) {
                    auto type = get<LexemeType>(matcher);
                    if (peek(i).get_type() != type)
                        return false;
                } else {
                    auto lexeme = get<Lexeme>(matcher);

                    if (peek(i) != lexeme)
                        return false;
                }
            }
            return true;
        }

        [[nodiscard]]
        ErrorOr<Identifier::IdentifierPtr> identifier() noexcept {

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

            return Identifier::create(name);
        }

        ErrorOr<Parameter::ParameterPtr> parameter() {

            auto i_type = identifier();
            auto i_name = identifier();

            VERIFY(i_type)
            VERIFY(i_name)

            auto name = get<Identifier::IdentifierPtr>(i_type)->get_name();
            auto type = get<Identifier::IdentifierPtr>(i_name)->get_name();

            if (match(COMMA)) advance();

            return Parameter::create(name, type);
        }

        ErrorOr<Declaration::DeclarationPtr> variable_declaration() {

            auto i_type = identifier();
            auto i_name = identifier();

            VERIFY(i_type)
            VERIFY(i_name)

            auto type = get<Identifier::IdentifierPtr>(i_type)->get_name();
            auto name = get<Identifier::IdentifierPtr>(i_name)->get_name();

            EXPECT(SEMICOLON)

            return Declaration::create(type, name);

        }

        ErrorOr<TokenListPtr> array_tokens() {

            EXPECT(LBRACKET)
            auto token_list = create_token_list();

            while (peek() != RBRACKET) {
                if (peek().get_type() == LexemeType::Literal) {
                    auto i_litreal = peek().get_data();
                    EXPECT_TYPE(LexemeType::Literal)
                    if (peek() != RBRACKET) {
                        EXPECT(COMMA)

                    }
                    token_list->push_back(Literal::create(i_litreal));
                } else {

                    advance();
                }
            }
            EXPECT(RBRACKET)
            return token_list;
        }

        ErrorOr<Declaration::DeclarationPtr> array_declaration_and_assignemnt() {

            auto type = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(LBRACKET)
            EXPECT(RBRACKET)

            auto name = peek().get_data();

            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(EQUALS)

            auto token_list = array_tokens();
            VERIFY(token_list)
            auto assignment = Assignment::create(name, get<TokenListPtr>(token_list), true);
            return Declaration::create(type, name, assignment, true);
        }

        ErrorOr<Declaration::DeclarationPtr> array_declaration() {

            auto type = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(LBRACKET)
            EXPECT(RBRACKET)

            auto name = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            return Declaration::create(type, name, nullptr, true);
        }

        ErrorOr<TokenListPtr> parse_expression() {

            std::deque<Lexeme> output; // queue
            std::deque<Lexeme> operators; // stack

            while (!match(SEMICOLON)) {
                auto x = peek();

                if (x.get_type() == LexemeType::Operator) {

                    while (!operators.empty() && operators.front().get_type() == LexemeType::Operator) {
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
                } else {
                    output.push_back(x);
                }
                advance();
            }

            while (!operators.empty()) {
                output.push_back(operators.front());
                operators.pop_front();
            }

            if (output.empty()) return "Failed parse assignment expression";
            auto token_list = create_token_list();


            for (auto &out_tok: output) {
                switch (out_tok.get_type()) {

                    case Operator:
                        token_list->push_back(Operator::create(out_tok.get_data()));
                        break;
                    case Literal:
                        token_list->push_back(Literal::create(out_tok.get_data()));
                        break;
                    default:
                        return fmt::format("Unknown token {} in expression\n", out_tok.to_string());
                }
            }
            return token_list;

        }

        ErrorOr<Declaration::DeclarationPtr> variable_declaration_and_assignment() {

            auto i_type = identifier();
            auto i_name = identifier();

            VERIFY(i_type)
            VERIFY(i_name)

            auto type = get<Identifier::IdentifierPtr>(i_type)->get_name();
            auto name = get<Identifier::IdentifierPtr>(i_name)->get_name();

            EXPECT(EQUALS)

            auto token_list = parse_expression();
            VERIFY(token_list)

            EXPECT(SEMICOLON)
            auto assignment = Assignment::create(name, get<TokenListPtr>(token_list));
            return Declaration::create(type, name, assignment);
        }

        ErrorOr<Assignment::AssignmentPtr> variable_assignment() {

            auto name = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(EQUALS)

            Assignment::AssignmentPtr assignment;

            if (peek() == LBRACKET) {
                auto array_token_list = array_tokens();
                VERIFY(array_token_list)

                assignment = Assignment::create(name, get<TokenListPtr>(array_token_list), true);
            } else {
                auto expression_token_list = parse_expression();
                VERIFY(expression_token_list)
                assignment = Assignment::create(name, get<TokenListPtr>(expression_token_list));
            }

            EXPECT(SEMICOLON)

            return assignment;
        }

        ErrorOr<Block::BlockPtr> block() noexcept {

            EXPECT(LCURLY)
            auto token_list = create_token_list();
            while (!match(RCURLY)) {

                if (match(Patterns::VariableAssignment)) {
                    auto var_assignment = variable_assignment();
                    VERIFY(var_assignment)
                    token_list->push_back(get<Assignment::AssignmentPtr>(var_assignment));
                } else if (match(Patterns::VariableDeclaration)) {
                    auto var_decl = variable_declaration();
                    VERIFY(var_decl)
                    token_list->push_back(get<Declaration::DeclarationPtr>(var_decl));

                } else if (match(Patterns::VariableDeclarationAndAssignment)) {
                    auto var_decl = variable_declaration_and_assignment();
                    VERIFY(var_decl)
                    token_list->push_back(get<Declaration::DeclarationPtr>(var_decl));
                } else if (match(Patterns::ArrayDeclaration)) {
                    auto arr_decl = array_declaration();
                    VERIFY(arr_decl)
                    token_list->push_back(get<Declaration::DeclarationPtr>(arr_decl));
                } else if (match(Patterns::ArrayDeclarationAndAssignment)) {
                    auto arr_decl = array_declaration_and_assignemnt();
                    VERIFY(arr_decl)
                    token_list->push_back(get<Declaration::DeclarationPtr>(arr_decl));
                } else {
                    advance();
                }

            }

            EXPECT(RCURLY)

            return Block::create(token_list);
        }

        ErrorOr<Function::FunctionPtr> function() {

            EXPECT(FN)

            auto name = identifier();

            VERIFY(name)

            EXPECT(LPAREN)

            auto params = Parameter::createLsit();

            while (!match(RPAREN)) {
                auto param = parameter();
                VERIFY(param)
                params->push_back(get<Parameter::ParameterPtr>(param));
            }

            EXPECT(RPAREN)

            auto parsed_block = block();

            VERIFY(parsed_block)

            return Function::create(params, get<Block::BlockPtr>(parsed_block),
                                    get<Identifier::IdentifierPtr>(name));

        }

    public:
        [[nodiscard]]
        const TokenList &get_tokens() const noexcept;

        explicit Parser(std::string file_name);

        [[nodiscard]]
        const LexemeList &get_lexemes() const noexcept;

        void parse();

    };

} // hasha

#endif //HASHA_PARSER_H

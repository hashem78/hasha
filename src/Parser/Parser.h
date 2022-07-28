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
#include "Tokens/VariableDeclaration.h"
#include "Operator.h"

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

        [[nodiscard]]
        inline bool match(const std::vector<std::variant<LexemeType, Lexeme>> &&matchers) const noexcept {

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

            if (match(Lexeme::COMMA)) advance();

            return Parameter::create(name, type);
        }

        ErrorOr<VariableDeclaration::VariableDeclarationPtr> variable_declaration() {

            auto i_type = identifier();
            auto i_name = identifier();

            VERIFY(i_type)
            VERIFY(i_name)

            auto type = get<Identifier::IdentifierPtr>(i_type)->get_name();
            auto name = get<Identifier::IdentifierPtr>(i_name)->get_name();

            EXPECT(Lexeme::SEMICOLON)

            return VariableDeclaration::create(type, name);

        }

        ErrorOr<TokenListPtr> array_tokens() {

            EXPECT(Lexeme::LBRACKET);
            auto token_list = create_token_list();

            while (peek() != Lexeme::RBRACKET) {
                if (peek().get_type() == LexemeType::Literal) {
                    auto i_litreal = peek().get_data();
                    EXPECT_TYPE(LexemeType::Literal)
                    if (peek() != Lexeme::RBRACKET) {
                        EXPECT(Lexeme::COMMA)

                    }
                    token_list->push_back(Literal::create(i_litreal));
                } else {

                    advance();
                }
            }
            EXPECT(Lexeme::RBRACKET);
            fmt::print("Here\n");
            return token_list;
        }

        ErrorOr<VariableDeclaration::VariableDeclarationPtr> array_declaration_and_assignemnt() {

            auto type = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(Lexeme::LBRACKET);
            EXPECT(Lexeme::RBRACKET);

            auto name = peek().get_data();

            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(Lexeme::EQUALS);

            auto token_list = array_tokens();
            VERIFY(token_list)

            return VariableDeclaration::create(type, name, get<TokenListPtr>(token_list), true);
        }

        ErrorOr<VariableDeclaration::VariableDeclarationPtr> array_declaration() {

            auto type = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            EXPECT(Lexeme::LBRACKET);
            EXPECT(Lexeme::RBRACKET);

            auto name = peek().get_data();
            EXPECT_TYPE(LexemeType::Identifier)
            return VariableDeclaration::create(type, name, nullptr, true);
        }

        ErrorOr<VariableDeclaration::VariableDeclarationPtr> variable_declaration_and_assignment() {

            auto i_type = identifier();
            auto i_name = identifier();

            VERIFY(i_type)
            VERIFY(i_name)

            auto type = get<Identifier::IdentifierPtr>(i_type)->get_name();
            auto name = get<Identifier::IdentifierPtr>(i_name)->get_name();

            EXPECT(Lexeme::EQUALS)
            std::deque<Lexeme> temp_lexemes;


            std::deque<Lexeme> output; // queue
            std::deque<Lexeme> operators; // stack

            while (!match(Lexeme::SEMICOLON)) {
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
                } else if (x == Lexeme::LPAREN) {
                    operators.push_front(x);
                } else if (x == Lexeme::RPAREN) {
                    while (operators.front() != Lexeme::LPAREN) {
                        // TODO: If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                        if (operators.empty()) break;
                        output.push_back(operators.front());
                        operators.pop_front();
                    }
                    // TODO: If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                    if (operators.front() != Lexeme::LPAREN)
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
                        break;
                }
            }


            EXPECT(Lexeme::SEMICOLON)

            return VariableDeclaration::create(type, name, token_list);
        }


        ErrorOr<Block::BlockPtr> block() noexcept {

            EXPECT(Lexeme::LCURLY)
            auto token_list = create_token_list();
            while (!match(Lexeme::RCURLY)) {

                if (match({LexemeType::Identifier, LexemeType::Identifier, Lexeme::SEMICOLON})) {
                    auto var_decl = variable_declaration();
                    VERIFY(var_decl)
                    token_list->push_back(get<VariableDeclaration::VariableDeclarationPtr>(var_decl));

                } else if (match(
                        {LexemeType::Identifier, LexemeType::Identifier, Lexeme::EQUALS})) {
                    auto var_decl = variable_declaration_and_assignment();
                    VERIFY(var_decl)
                    token_list->push_back(get<VariableDeclaration::VariableDeclarationPtr>(var_decl));
                } else if
                        (match({LexemeType::Identifier,
                                Lexeme::LBRACKET, Lexeme::RBRACKET, LexemeType::Identifier, Lexeme::SEMICOLON})) {
                    auto arr_decl = array_declaration();
                    VERIFY(arr_decl)
                    token_list->push_back(get<VariableDeclaration::VariableDeclarationPtr>(arr_decl));
                } else if (match({LexemeType::Identifier,
                                  Lexeme::LBRACKET, Lexeme::RBRACKET, LexemeType::Identifier, Lexeme::EQUALS})) {
                    auto arr_decl = array_declaration_and_assignemnt();
                    VERIFY(arr_decl)
                    token_list->push_back(get<VariableDeclaration::VariableDeclarationPtr>(arr_decl));
                } else {
                    advance();
                }

            }

            EXPECT(Lexeme::RCURLY)

            return Block::create(token_list);
        }

        ErrorOr<Function::FunctionPtr> function() {

            EXPECT(Lexeme::FN)

            auto name = identifier();

            VERIFY(name)

            EXPECT(Lexeme::LPAREN)

            auto params = Parameter::createLsit();

            while (!match(Lexeme::RPAREN)) {
                auto param = parameter();
                VERIFY(param)
                params->push_back(get<Parameter::ParameterPtr>(param));
            }

            EXPECT(Lexeme::RPAREN)

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

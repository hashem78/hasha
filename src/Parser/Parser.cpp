//
// Created by mythi on 21/07/22.
//

#include <thread>
#include <utility>
#include "Parser.h"
#include "Expressions/ArrayExpression.h"
#include "Expressions/LiteralExpression.h"

#define EXPECT(lexeme) if(!expect(lexeme)){ cursor = before; return false;}
#define EXPECT_PTR(lexeme) if(!expect(lexeme)){ cursor = before; return nullptr;}
#define EXPECT_L(lexeme) if(!expect(lexeme)){ cursor = before; break;}

namespace hasha {
    Parser::Parser(std::string file_name) : lexer(std::move(file_name)), cursor(0) {

        lexer.lex();
        lexemes = lexer.get_lexemes();
    }

    void Parser::parse() {

        while (!done()) {
            parse_function();
        }

    }

    const LexemeList &Parser::get_lexemes() const {

        return lexemes;
    }

    Lexeme Parser::peek(int k) const {

        if (cursor + k < lexemes.size()) return lexemes[cursor + k];

        return lexemes.back();
    }

    bool Parser::exists_from(const Lexeme &lexeme, int from) const {

        if (from >= lexemes.size() || from < 0) return false;

        for (int i = from; i < lexemes.size(); ++i)
            if (lexeme == lexemes[i])
                return true;

        return false;
    }

    bool Parser::expect(const LexemeType &lexeme_type) {


        if (lexeme_type == peek().get_type()) {
            if (!done())
                next();
            return true;
        }

        fmt::print("Expected {} found {}\n", magic_enum::enum_name(lexeme_type), peek().to_string());

        return false;
    }

    bool Parser::expect(const Lexeme &lexeme) {


        if (lexeme == peek()) {
            if (!done())
                next();
            return true;
        }

        fmt::print("Expected {} found {}\n", lexeme.to_string(), peek().to_string());

        return false;

    }

    bool Parser::done() const {

        return cursor >= lexemes.size();
    }

    void Parser::add_token(TokenPtr ptr) {

        tokens.push_back(std::move(ptr));
    }

    bool Parser::parse_function() {

        auto before = cursor;
        EXPECT(Lexeme::FN)

        auto name = peek().get_data();
        EXPECT(LexemeType::Identifier);

        EXPECT(Lexeme::LBRACE)

        auto parameters = parse_parameters();

        EXPECT(Lexeme::RBRACE)

        EXPECT(Lexeme::LCURLY)

        auto block = parse_block();

        if (!block) {
            cursor = before;
            fmt::print("Failed to parse block for {}\n", name);
            return false;
        }

        EXPECT(Lexeme::RCURLY)

        auto function = Function::create(parameters, block, name);
        add_token(function);

        return true;
    }

    ParameterListPtr Parser::parse_parameters() {

        auto before = cursor;

        auto params = create_parameter_list();

        while (peek() != Lexeme::RBRACE) {

            bool is_array_declaration = false;
            auto type = peek().get_data();
            EXPECT_L(LexemeType::Identifier)

            if (is_array_decl()) {
                is_array_declaration = true;
                EXPECT_PTR(Lexeme::LBRACKET);
                EXPECT_PTR(Lexeme::RBRACKET);
            }

            auto name = peek().get_data();
            EXPECT_L(LexemeType::Identifier)
            if (peek() == Lexeme::COMMA) next();

            if (is_array_declaration) {

                params->push_back(ArrayDeclaration::create(type, name));
            } else {

                params->push_back(VariableDeclaration::create(type, name));
            }
        }
        return params;
    }

    const TokenList &Parser::get_tokens() const {

        return tokens;
    }

    Block::BlockPtr Parser::parse_block() {

        if (!exists_from(Lexeme::RCURLY, cursor)) return nullptr;

        auto token_list = create_token_list();

        while (peek() != Lexeme::RCURLY) {
            auto var_decl = parse_variable_declaration();
            if (var_decl != nullptr) {
                token_list->push_back(var_decl);
            }
            auto var_assignment = parse_variable_assignment();
            if (var_assignment != nullptr) {
                token_list->push_back(var_assignment);
            }
        }


        return Block::create(token_list);
    }

    ArrayExpression::ArrayExpressionPtr Parser::parse_array() {

        auto before = cursor;

        EXPECT_PTR(Lexeme::LBRACKET)
        auto expressions = create_expression_list();
        while (peek() != Lexeme::RBRACKET) {

            auto literal = peek().get_data();
            EXPECT_L(LexemeType::Literal)

            if (peek() == Lexeme::COMMA) next();

            auto literal_expression = LiteralExpression::create(literal);
            expressions->push_back(literal_expression);
        }
        EXPECT_PTR(Lexeme::RBRACKET)
        return ArrayExpression::create(expressions);
    }

    ArrayDeclaration::ArrayDeclarationPtr Parser::parse_array_declaration_of_type(std::string type) {

        auto before = cursor;

        EXPECT_PTR(Lexeme::LBRACKET);
        EXPECT_PTR(Lexeme::RBRACKET);

        auto name = peek().get_data();
        EXPECT_PTR(LexemeType::Identifier)
        EXPECT_PTR(Lexeme::EQUALS)

        if (peek() == Lexeme::LBRACKET) {

            auto array_expression = parse_array();

            if (!array_expression) return nullptr;

            auto decl = ArrayDeclaration::create(std::move(type), name, array_expression);

            return decl;
        }

        return nullptr;
    }

    VariableDeclaration::VariableDeclarationPtr Parser::parse_variable_declaration() {


        auto before = cursor;

        auto type = peek().get_data();
        EXPECT_PTR(LexemeType::Identifier);

        VariableDeclaration::VariableDeclarationPtr variable_declaration;

        if (is_array_decl()) {

            variable_declaration = parse_array_declaration_of_type(type);
        } else {

            auto name = peek().get_data();

            EXPECT_PTR(LexemeType::Identifier);

            if (peek() == Lexeme::EQUALS) {
                EXPECT_PTR(Lexeme::EQUALS)

                auto literal = peek().get_data();
                EXPECT_PTR(LexemeType::Literal);
                auto expression = LiteralExpression::create(literal);
                variable_declaration = VariableDeclaration::create(type, name, expression);
            }

            variable_declaration = VariableDeclaration::create(type, name);
        }
        EXPECT_PTR(Lexeme::SEMICOLON);

        return variable_declaration;
    }

    void Parser::next() {

        if (!done())
            cursor++;
    }

    VariableAssignment::VariableAssignmentPtr Parser::parse_variable_assignment() {


        auto before = cursor;
        VariableAssignment::VariableAssignmentPtr variable_assignment;

        auto name = peek().get_data();
        EXPECT_PTR(LexemeType::Identifier)

        EXPECT_PTR(Lexeme::EQUALS)


        if (peek() == Lexeme::LBRACKET) {
            auto array_expression = parse_array();
            variable_assignment = VariableAssignment::create(name, array_expression);
        }

        if (peek().get_type() == LexemeType::Literal) {
            auto value = peek().get_data();
            EXPECT_PTR(LexemeType::Literal)
            variable_assignment = VariableAssignment::create(name, LiteralExpression::create(value));
        }

        EXPECT_PTR(Lexeme::SEMICOLON)


        return variable_assignment;

    }

    bool Parser::is_array_decl() const {

        return peek() == Lexeme::LBRACKET && peek(1) == Lexeme::RBRACKET;
    }


} // hasha
//
// Created by mythi on 21/07/22.
//

#include "Parser.h"

#define EXPECT(lexeme) if(!expect(lexeme)){ cursor = before; return false;}
#define EXPECT_PTR(lexeme) if(!expect(lexeme)){ cursor = before; return nullptr;}
#define EXPECT_L(lexeme) if(!expect(lexeme)){ cursor = before; break;}

namespace hasha {
    Parser::Parser(std::string file_name) : lexer(std::move(file_name)), cursor(0) {

        lexer.lex();
        lexemes = lexer.get_lexemes();
    }

    void Parser::parse() {

        parse_function();

    }

    const LexemeList &Parser::get_lexemes() const {

        return lexemes;
    }

    Lexeme Parser::peek(int k) {

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

        fmt::print("Expected {} found {}\n", peek().to_string(),
                   magic_enum::enum_name(lexeme_type));

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

            auto type = peek().get_data();
            EXPECT_L(LexemeType::Identifier)

            auto name = peek().get_data();
            EXPECT_L(LexemeType::Identifier)
            if (peek() == Lexeme::COMMA) next();

            auto declaration = VariableDeclaration::create(type, name);
            params->push_back(declaration);
        }
        return params;
    }

    const TokenList &Parser::get_tokens() const {

        return tokens;
    }

    Block::BlockPtr Parser::parse_block() {

        if (!exists_from(Lexeme::RCURLY, cursor)) return nullptr;

        auto token_list = create_token_list();

        auto is_var_decl = [this]() -> bool {
            return peek().get_type() == LexemeType::Identifier && peek(1).get_type() == LexemeType::Identifier;
        };
        while (is_var_decl()) {
            auto var_decl = parse_variable_declaration();
            if (var_decl != nullptr) {
                token_list->push_back(var_decl);
            }
        }


        return Block::create(token_list);
    }

    VariableDeclaration::VariableDeclarationPtr Parser::parse_variable_declaration() {

        auto before = cursor;

        auto type = peek().get_data();
        EXPECT_PTR(LexemeType::Identifier);

        auto name = peek().get_data();
        EXPECT_PTR(LexemeType::Identifier);

        auto declaration = VariableDeclaration::create(type, name);

        return declaration;
    }

    void Parser::next() {

        if (!done())
            cursor++;
    }


} // hasha
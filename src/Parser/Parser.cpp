//
// Created by mythi on 21/07/22.
//

#include <thread>
#include <utility>
#include "Parser.h"

namespace hasha {
    Parser::Parser(std::string file_name) : lexer(std::move(file_name)), cursor(0) {

        lexer.lex();
        lexemes = lexer.get_lexemes();
    }

    void Parser::parse() {

        auto fn = function();
        if (holds_alternative<ParseError>(fn))
            fmt::print("{}\n", get<ParseError>(fn));
        else {
            fmt::print("{}\n", get<Function::FunctionPtr>(fn)->to_string());
        }
    }

    const LexemeList &Parser::get_lexemes() const noexcept {

        return lexemes;
    }

    Lexeme Parser::peek(std::size_t k) const noexcept {

        if (cursor + k < lexemes.size()) return lexemes[cursor + k];

        return lexemes.back();
    }


    const TokenList &Parser::get_tokens() const noexcept {

        return tokens;
    }


} // hasha
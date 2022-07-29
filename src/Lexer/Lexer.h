//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXER_H
#define HASHA_LEXER_H

#include "Lexeme.h"

#include <fstream>

#include "fmt/format.h"

namespace hasha {

    class Lexer {
    public:
        explicit Lexer(std::string file_name);

        void lex();

        const LexemeList &get_lexemes() const;

    private:

        LexemeList m_lexemes;
        std::string m_file_name;
        std::vector<char> m_data;
        std::vector<std::unique_ptr<std::string>> m_produced_literals;
        std::vector<std::unique_ptr<std::string>> m_produced_identifiers;
        int m_cursor;

        static bool is_legal(char c);

        std::string next_token();

        [[nodiscard]]
        bool done() const;

        [[nodiscard]]
        char peek(int= 0) const;

        static bool is_numeric_literal(const std::string &str);

        static bool is_string_literal(const std::string &token);

        static bool is_identifier(std::string token) ;
    };

} // hasha

#endif //HASHA_LEXER_H

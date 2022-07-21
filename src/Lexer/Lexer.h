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
        int m_cursor;

        static bool is_legal(char c);

        std::string next_token();

        [[nodiscard]]
        bool done() const;

        [[nodiscard]]
        char peek_char(int= 0) const;

        static bool is_literal(std::string str);

    };

} // hasha

#endif //HASHA_LEXER_H

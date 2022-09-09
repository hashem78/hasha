//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXER_H
#define HASHA_LEXER_H

#include <vector>

#include "Lexeme.h"
#include "ErrorOr.h"



namespace hasha {

    class Lexer {
    public:
        explicit Lexer(std::string);

        ErrorOr<void> lex();

        [[nodiscard]]
        const LexemeList &get_lexemes() const;

        std::vector<char> data;
    private:

        LexemeList lexemes;
        std::string file_name;
        int cursor;
        int line;
        int col;

        std::pair<std::string, Span> next_token() noexcept;

        void skip_spaces() noexcept;

        [[nodiscard]]
        bool done() const noexcept;

        [[nodiscard]]
        char peek(int= 0) const noexcept;

        static bool is_legal_character(char) noexcept;

        static bool is_numeric_literal(std::string_view) noexcept;

        static bool is_string_literal(std::string_view) noexcept;

        static bool is_identifier(std::string_view) noexcept;
    };

} // hasha

#endif //HASHA_LEXER_H

//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXER_H
#define HASHA_LEXER_H

#include <vector>

#include "ErrorOr.h"
#include "Lexeme.h"


namespace hasha {

  class Lexer {
   public:
    explicit Lexer(std::string);

    ErrorOr<void> lex();

    [[nodiscard]] const LexemeList &get_lexemes() const;

    std::vector<char> data;

   private:
    LexemeList lexemes;
    std::string file_name;
    size_t cursor;
    size_t line;
    size_t col;

    ErrorOr<Lexeme> next_token() noexcept;

    void skip_spaces() noexcept;

    void advance(int k = 1);

    [[nodiscard]] bool done() const noexcept;

    [[nodiscard]] bool match(std::string_view str) noexcept;

    [[nodiscard]] char peek(int = 0) const noexcept;

    [[nodiscard]] std::string collect() noexcept;

    static bool is_legal_character(char) noexcept;

    static bool is_numeric_literal(std::string_view str) noexcept;

    static bool is_identifier(std::string_view) noexcept;
  };

}// namespace hasha

#endif//HASHA_LEXER_H

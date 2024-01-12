//
// Created by mythi on 21/07/22.
//

#include <cctype>
#include <fstream>

#include "Analyzer.h"
#include "Constants.h"
#include "Lexer.h"
#include "fmt/core.h"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/trim.hpp"

#define MATCH_LEXEME(STRING_REP, LEXEME) \
  if (match(STRING_REP)) return LEXEME.with_span(create_span())

namespace hasha {

  Lexer::Lexer(std::string file_name)
      : file_name(std::move(file_name)),
        cursor(0),
        line(1),
        col(1) {

    std::ifstream file(this->file_name, std::ios::binary);

    if (!file.is_open() || !file.good()) {
      fmt::print("Failed to open {}", this->file_name);
      exit(1);
    }
    data = std::vector(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    data = data | ranges::views::trim([](char c) { return std::isspace(c); }) | ranges::to<std::vector>();
  }

  ErrorOr<void> Lexer::lex() {

    while (!done()) {

      auto lexeme = TRY(next_token());
      if (lexeme.type() == LexemeType::ILLEGAL) {
        return fmt::format(
          "Illegal token {} on line: {}, col: {}",
          lexeme.data(),
          lexeme.span().line,
          lexeme.span().col
        );
      }
      lexemes.push_back(lexeme);
    }
    lexemes.push_back(EOFL);

    Analyzer analyzer(lexemes);
    TRY(analyzer.analyze_bracket_pairs());

    return {};
  }

  bool Lexer::is_identifier(std::string_view token) noexcept {

    if (token.empty()) return false;
    if (std::isdigit(token.front())) return false;

    return std::none_of(
             token.begin(),
             token.end(),
             [](char c) { return is_legal_character(c); }
           ) &&
           std::all_of(
             token.begin(),
             token.end(),
             [](char c) { return std::isalnum(c) || c == '_'; }
           );
  }

  bool Lexer::is_legal_character(char c) noexcept {

    static const auto special = std::string("{}[]()=+-*/%,<>!&^~.|;:\"");

    return std::any_of(
      special.begin(),
      special.end(),
      [&c](char chr) { return chr == c; }
    );
  }

  ErrorOr<Lexeme> Lexer::next_token() noexcept {

    if (done()) return Lexeme{{}, {}, {}, Span{}};

    skip_spaces();
    size_t begin = cursor;
    size_t start_col = col;
    auto create_span = [&, this]() -> Span {
      return Span{begin, cursor, line, start_col};
    };

    auto try_math_operator = [&create_span, this](
                               char op,
                               const Lexeme &unary_version,
                               const Lexeme &binary_version
                             ) -> std::optional<Lexeme> {
      if (peek() == op) {
        const auto &previous_lexeme = lexemes.back();
        // Check the previous lexeme

        // UNARY
        // -----
        // OPERATOR
        if (previous_lexeme.type() == LexemeType::OPERATOR) {
          advance();
          return unary_version.with_span(create_span());
        }

        // LPAREN
        if (previous_lexeme == LPAREN) {
          advance();
          return unary_version.with_span(create_span());
        }
        // EQUALS
        if (previous_lexeme == EQUALS) {
          advance();
          return unary_version.with_span(create_span());
        }

        // BINRAY
        // -----
        // LITERAL
        if (previous_lexeme.type() == LexemeType::LITERAL) {
          advance();
          return binary_version.with_span(create_span());
        }
        // Identifier
        if (previous_lexeme.type() == LexemeType::IDENTIFIER) {
          advance();
          return binary_version.with_span(create_span());
        }
        // RPAREN
        if (previous_lexeme == RPAREN) {
          advance();
          return binary_version.with_span(create_span());
        }
      }
      return {};
    };

    // Match Keywords
    {
      MATCH_LEXEME("fn", FN);
      MATCH_LEXEME("if", IF);
      MATCH_LEXEME("else", ELSE);
      MATCH_LEXEME("elif", ELIF);
      MATCH_LEXEME("return", RETURN);
      MATCH_LEXEME("true", TRUE);
      MATCH_LEXEME("false", FALSE);
    };

    // Match Symbols
    {
      MATCH_LEXEME("{", LCURLY);
      MATCH_LEXEME("}", RCURLY);
      MATCH_LEXEME("(", LPAREN);
      MATCH_LEXEME(")", RPAREN);
      MATCH_LEXEME("<", LANGEL);
      MATCH_LEXEME(">", RANGEL);
      MATCH_LEXEME("[", LBRACKET);
      MATCH_LEXEME("]", RBRACKET);
      MATCH_LEXEME(",", COMMA);
      MATCH_LEXEME(";", SEMICOLON);
      MATCH_LEXEME(":", COLON);
      MATCH_LEXEME("->", ARROW);
    }

    // Match Binary Operators
    {
      MATCH_LEXEME("&&", LAND);
      MATCH_LEXEME("||", LOR);
      MATCH_LEXEME("->", ARROW);
      MATCH_LEXEME("=", EQUALS);
      MATCH_LEXEME("*", ASTERISK);
      MATCH_LEXEME("/", FSLASH);
    }

    // Operators with unary versions
    if (auto op = try_math_operator('+', UNARY_PLUS, BINARY_PLUS))
      return op.value();
    if (auto op = try_math_operator('-', UNARY_MINUS, BINARY_MINUS))
      return op.value();


    // String Literals
    if (peek() == '"') {
      auto string_ltrl = std::string{};
      do {
        string_ltrl += peek();
        advance();
      } while (peek() != '"');
      string_ltrl += '"';
      advance();
      return Lexeme{string_ltrl, LexemeType::LITERAL, LiteralType::String, create_span()};
    }


    // Collect chars
    auto token = collect();

    // If all the collected chars are digits we have a numeric literal
    if (is_numeric_literal(token)) {
      if (peek() == '.') {
        advance();
        auto decimal_part = collect();
        if (!is_numeric_literal(decimal_part)) {
          auto span = create_span();
          return fmt::format(
            "Expected a decimal part for literal {} on line: {}, col {}",
            token,
            span.line,
            span.col
          );
        }
        return Lexeme{
          fmt::format("{}.{}", token, decimal_part),
          LexemeType::LITERAL,
          LiteralType::Float,
          create_span()
        };
      }
      return Lexeme{token, LexemeType::LITERAL, LiteralType::Integer, create_span()};
    }

    if (is_identifier(token))
      return Lexeme{token, LexemeType::IDENTIFIER, {}, create_span()};

    return Lexeme{token, LexemeType::ILLEGAL};
  }

  bool Lexer::done() const noexcept {

    return cursor >= data.size();
  }

  char Lexer::peek(int k) const noexcept {

    if (cursor + k < data.size()) {
      return data[cursor + k];
    }
    return data[cursor];
  }

  const LexemeList &Lexer::get_lexemes() const {

    return lexemes;
  }

  void Lexer::skip_spaces() noexcept {

    while (std::isspace(peek()) && !done()) {
      if (peek() == '\n') {
        line++;
        col = 0;
      }

      col++;
      cursor++;
    }
  }

  bool Lexer::match(std::string_view str) noexcept {

    int i = 0;
    for (const auto &x: str) {
      if (peek(i++) != x)
        return false;
    }
    advance(static_cast<int>(str.size()));
    return true;
  }

  void Lexer::advance(int k) {

    cursor += k;
    col += k;
  }

  bool Lexer::is_numeric_literal(std::string_view str) noexcept {

    if (str.empty())
      return false;
    return std::all_of(str.cbegin(), str.cend(), [](char c) { return std::isdigit(c); });
  }

  std::string Lexer::collect() noexcept {

    auto token = std::string{};
    while (std::isalnum(peek()) || peek() == '_') {
      token += peek();
      advance();
    }
    return token;
  }

}// namespace hasha

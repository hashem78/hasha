//
// Created by mythi on 21/07/22.
//

#include "Lexer.h"

namespace hasha {

    Lexer::Lexer(std::string file_name) {

        this->cursor = 0;
        this->file_name = std::move(file_name);

        std::ifstream file(this->file_name, std::ios::binary);

        if (!file.is_open() || !file.good()) {
            fmt::print("Failed to open {}\n", this->file_name);
            exit(1);
        }

        data = std::vector(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    }

    ErrorOr<void> Lexer::lex() {

        while (!done()) {

            auto token = next_token();

            if (lexeme_map.contains(token)) {
                lexemes.push_back(lexeme_map.at(token));
            } else if (is_numeric_literal(token)) {
                lexemes.push_back({token, LexemeType::NUMERIC_LITERAL});
            } else if (is_string_literal(token)) {
                lexemes.push_back({token, LexemeType::STRING_LITERAL});
            } else if (is_identifier(token)) {
                lexemes.push_back({token, LexemeType::IDENTIFIER});
            } else {
                return fmt::format("LEXER: Illegal Token {}", token);
            }
        }
        return {};

    }

    bool Lexer::is_identifier(std::string_view token) noexcept {

        if (token.empty()) return false;
        if (std::isdigit(token.front())) return false;

        return std::none_of(
                token.begin(),
                token.end(),
                [](char c) { return is_legal_character(c); })
               && std::all_of(
                token.begin(),
                token.end(),
                [](char c) { return std::isalnum(c) || c == '_'; }
        );

    }

    bool Lexer::is_legal_character(char c) noexcept {

        static const auto special = std::string("{}[]()=+-*/%,<>!&^~.|;\"");

        return std::any_of(
                special.begin(),
                special.end(),
                [&c](char chr) { return chr == c; }
        );

    }

    bool Lexer::is_numeric_literal(std::string_view str) noexcept {

        if (str.empty())
            return false;

        return std::all_of(
                str.begin(),
                str.end(),
                [](char c) { return std::isdigit(c); }
        );
    }

    std::string Lexer::next_token() {

        if (done()) return {};

        skip_spaces();
        if (peek() == '&' && peek(1) == '&') {
            cursor += 2;
            return "&&";
        }
        if (peek() == '|' && peek(1) == '|') {
            cursor += 2;
            return "||";
        }
        if (peek() == '-' && peek(1) == '>') {
            cursor += 2;
            return "->";
        }
        if (peek() == '"') {
            auto string_ltrl = std::string{};
            do {
                string_ltrl += peek();
                cursor++;
            } while (peek() != '"');
            string_ltrl += '"';
            cursor++;
            return string_ltrl;
        }
        if (is_legal_character(peek())) {
            cursor++;
            return std::string{peek(-1)};
        }

        auto token = std::string{};
        while (std::isalnum(peek()) || peek() == '_') {
            token += peek();
            cursor++;
        }
        return token;

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

    bool Lexer::is_string_literal(std::string_view token) noexcept {

        return token.front() == '\"' && token.back() == '\"';
    }

    void Lexer::skip_spaces() noexcept {

        while (std::isspace(peek()) && !done()) {
            cursor++;
        }

    }

} // hasha
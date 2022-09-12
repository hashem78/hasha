//
// Created by mythi on 21/07/22.
//

#include <fstream>


#include "fmt/format.h"

#include "Analyzer.h"
#include "Constants.h"
#include "Lexer.h"

namespace hasha {

    Lexer::Lexer(std::string file_name) :
            file_name(std::move(file_name)),
            cursor(0),
            line(1),
            col(1) {

        std::ifstream file(this->file_name, std::ios::binary);

        if (!file.is_open() || !file.good()) {
            fmt::print("Failed to open {}\n", this->file_name);
            exit(1);
        }

        data = std::vector(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    }

    ErrorOr<void> Lexer::lex() {

        while (!done()) {

            auto [token, span] = next_token();

            if (lexeme_map.contains(token)) {
                auto lexeme = lexeme_map.at(token);
                lexeme.set_span(span);

                lexemes.push_back(lexeme);
            } else if (is_numeric_literal(token)) {

                lexemes.push_back({token, LexemeType::NUMERIC_LITERAL, span});
            } else if (is_string_literal(token)) {

                lexemes.push_back({token, LexemeType::STRING_LITERAL, span});
            } else if (is_identifier(token)) {

                lexemes.push_back({token, LexemeType::IDENTIFIER, span});
            } else {
                return fmt::format("LEXER: Illegal Token {} on line: {} col {}", token, span.line, span.col);
            }
        }

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

    std::pair<std::string, Span> Lexer::next_token() noexcept {

        if (done()) return {{}, Span{}};

        skip_spaces();
        int begin = cursor;
        int start_col = col;
        if (peek() == '&' && peek(1) == '&') {
            cursor += 2;
            col += 2;
            return {"&&", Span{begin, cursor, line, start_col}};
        }
        if (peek() == '|' && peek(1) == '|') {
            cursor += 2;
            col += 2;
            return {"||", Span{begin, cursor, line, start_col}};
        }
        if (peek() == '-' && peek(1) == '>') {
            cursor += 2;
            col += 2;
            return {"->", Span{begin, cursor, line, start_col}};
        }
        if (peek() == '"') {
            auto string_ltrl = std::string{};
            do {
                string_ltrl += peek();
                col++;
                cursor++;
            } while (peek() != '"');
            string_ltrl += '"';
            cursor++;
            col++;
            return {string_ltrl, Span{begin, cursor, line, start_col}};
        }
        if (is_legal_character(peek())) {
            cursor++;
            col++;
            return {std::string{peek(-1)}, Span{begin, cursor, line, start_col}};
        }

        auto token = std::string{};
        while (std::isalnum(peek()) || peek() == '_') {
            token += peek();
            cursor++;
            col++;
        }
        return {token, Span{begin, cursor, line, start_col}};

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
            if (peek() == '\n') {
                line++;
                col = 0;
            }

            col++;
            cursor++;
        }
    }

} // hasha
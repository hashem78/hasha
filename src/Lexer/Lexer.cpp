//
// Created by mythi on 21/07/22.
//

#include "Lexer.h"

namespace hasha {

    Lexer::Lexer(std::string file_name) {

        this->m_cursor = 0;
        this->m_file_name = std::move(file_name);

        std::ifstream file(this->m_file_name, std::ios::binary);

        if (!file.is_open() || !file.good()) {
            fmt::print("Failed to open {}\n", this->m_file_name);
            exit(1);
        }

        m_data = std::vector(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    }

    ErrorOr<void> Lexer::lex() {

        while (!done()) {

            auto token = next_token();

            if (token.empty()) continue;

            if (lexeme_map.contains(token)) {
                m_lexemes.push_back(lexeme_map.at(token));
            } else if (is_numeric_literal(token)) {
                m_lexemes.push_back({token, LexemeType::NUMERIC_LITERAL});
            } else if (is_string_literal(token)) {
                m_lexemes.push_back({token, LexemeType::STRING_LITERAL});
            } else if (is_identifier(token)) {
                m_lexemes.push_back({token, LexemeType::IDENTIFIER});
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

        auto token = std::string();

        while (!done()) {

            auto curr = peek();

            if (std::isspace(curr)) {
                m_cursor++;
                return token;
            }

            if (!std::isalnum(curr) && curr != '_') {
                if (!is_legal_character(curr)) {
                    token += curr;
                    m_cursor++;
                }
                break;
            }


            token += curr;
            m_cursor++;

        }

        if (token.empty() && !done()) {
            if (is_legal_character(peek())) {
                if (peek() == '\"') {
                    token += '\"';
                    m_cursor++;

                    while (peek() != '\"') {
                        token += peek();
                        m_cursor++;
                    }

                    token += '\"';
                    m_cursor++;

                } else {

                    if (peek() == '-' && peek(1) == '>') {
                        token += "->";
                        m_cursor += 2;
                    } else if (peek() == '&' && peek(1) == '&') {
                        token += "&&";
                        m_cursor += 2;
                    } else if (peek() == '|' && peek(1) == '|') {
                        token += "||";
                        m_cursor += 2;
                    } else {
                        token += peek();
                        m_cursor++;
                    }
                }
            }
        }

        return token;
    }

    bool Lexer::done() const noexcept {

        return m_cursor >= m_data.size();
    }

    char Lexer::peek(int k) const noexcept {

        if (m_cursor + k < m_data.size()) {
            return m_data[m_cursor + k];
        }
        return m_data[m_cursor];
    }

    const LexemeList &Lexer::get_lexemes() const {

        return m_lexemes;
    }

    bool Lexer::is_string_literal(std::string_view token) noexcept {

        return token.front() == '\"' && token.back() == '\"';
    }

} // hasha
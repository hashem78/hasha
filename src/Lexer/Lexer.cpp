//
// Created by mythi on 21/07/22.
//

#include "Lexer.h"

#include <utility>
#include <thread>

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

    void Lexer::lex() {

        while (!done()) {

            auto token = next_token();
            if (token.empty()) continue;


            if (token == "fn") {
                m_lexemes.push_back(FN);
            } else if (token == "{") {
                m_lexemes.push_back(LCURLY);
            } else if (token == "}") {
                m_lexemes.push_back(RCURLY);
            } else if (token == "(") {
                m_lexemes.push_back(LPAREN);
            } else if (token == ")") {
                m_lexemes.push_back(RPAREN);
            } else if (token == "[") {
                m_lexemes.push_back(LBRACKET);
            } else if (token == "]") {
                m_lexemes.push_back(RBRACKET);
            } else if (token == ",") {
                m_lexemes.push_back(COMMA);
            } else if (token == "=") {
                m_lexemes.push_back(EQUALS);
            } else if (token == "+") {
                m_lexemes.push_back(ADDITION);
            } else if (token == "-") {
                m_lexemes.push_back(HYPHEN);
            } else if (token == "*") {
                m_lexemes.push_back(ASTERISK);
            } else if (token == "/") {
                m_lexemes.push_back(FSLASH);
            } else if (token == ";") {
                m_lexemes.push_back(SEMICOLON);
            } else if (token == "->") {
                m_lexemes.push_back(ARROW);
            } else if (is_numeric_literal(token)) {
                m_produced_literals.push_back(std::make_unique<std::string>(token));
                m_lexemes.push_back({m_produced_literals.back()->c_str(), LexemeType::Literal});
            } else if (is_string_literal(token)) {
                m_produced_literals.push_back(std::make_unique<std::string>(token));
                m_lexemes.push_back({m_produced_literals.back()->c_str(), LexemeType::Literal});
            } else {
                m_produced_identifiers.push_back(std::make_unique<std::string>(token));
                m_lexemes.push_back({m_produced_identifiers.back()->c_str(), LexemeType::Identifier});
            }
        }

    }

    bool Lexer::is_legal(char c) {

        auto special = std::string("{}[]()=+-*/%,<>!&^~.|;\"");
        for (auto ch: special)
            if (ch == c)
                return true;
        return false;
    }

    bool Lexer::is_numeric_literal(const std::string &str) {

        if (str.empty())
            return false;
        for (auto ch: str)
            if (!std::isdigit(ch)) return false;
        return true;
    }


    std::string Lexer::next_token() {

        auto token = std::string();

        while (!done()) {

            auto curr = peek();

            if (std::isspace(curr)) {
                m_cursor++;
                break;
            }

            if (!std::isalnum(curr)) {
                break;
            }


            token += curr;
            m_cursor++;

        }

        if (token.empty() && !done()) {
            if (is_legal(peek())) {
                if (peek() == '\"') {
                    token += '\"';
                    m_cursor++;

                    while (peek() != '\"') {
                        token += peek();
                        m_cursor++;
                    }

                    token += '\"';
                    m_cursor++;

                } else if (peek() == '-' && peek(1) == '>') {
                    token = "->";
                    m_cursor += 2;
                } else {
                    token += peek();
                    m_cursor++;
                }
            }
        }


        return token;
    }

    bool Lexer::done() const {

        return m_cursor >= m_data.size();
    }

    char Lexer::peek(int k) const {

        if (m_cursor + k < m_data.size()) {
            return m_data[m_cursor + k];
        }
        return m_data[m_cursor];
    }

    const LexemeList &Lexer::get_lexemes() const {

        return m_lexemes;
    }

    bool Lexer::is_string_literal(const std::string &token) {

        return token.front() == '\"' && token.back() == '\"';
    }

} // hasha
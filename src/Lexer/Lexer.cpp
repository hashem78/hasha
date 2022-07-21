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
                m_lexemes.push_back(Lexeme::FN);
            } else if (token == "{") {
                m_lexemes.push_back(Lexeme::LCURLY);
            } else if (token == "}") {
                m_lexemes.push_back(Lexeme::RCURLY);
            } else if (token == "(") {
                m_lexemes.push_back(Lexeme::LBRACE);
            } else if (token == ")") {
                m_lexemes.push_back(Lexeme::RBRACE);
            } else if (token == ",") {
                m_lexemes.push_back(Lexeme::COMMA);
            } else {
                m_lexemes.emplace_back(token, LexemeType::Identifier);
            }
        }
    }

    bool Lexer::is_legal(char c) {

        auto special = std::string("{}[]()=+-*/%,<>!&^~.|;");
        for (auto ch: special)
            if (ch == c)
                return true;
        return false;
    }


    std::string Lexer::next_token() {

        auto token = std::string();

        while (!done()) {

            auto curr = peek_char();

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
            if (is_legal(peek_char())) {
                token += peek_char();
                m_cursor++;
            }
        }


        return token;
    }

    bool Lexer::done() const {

        return m_cursor >= m_data.size();
    }

    char Lexer::peek_char(int k) const {

        if (m_cursor + k < m_data.size()) {
            return m_data[m_cursor + k];
        }
        return m_data[m_cursor];
    }

    const LexemeList &Lexer::get_lexemes() const {

        return m_lexemes;
    }

} // hasha
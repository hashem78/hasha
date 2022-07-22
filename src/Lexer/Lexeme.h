//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXEME_H
#define HASHA_LEXEME_H

#include <string>
#include <deque>
#include <utility>

#include "nlohmann/json.hpp"
#include "magic_enum.hpp"
#include "fmt/format.h"

namespace hasha {

    enum LexemeType {
        Operator,
        Identifier,
        Literal,
        Symbol,
        Keyword,
    };

    class Lexeme {
        std::string m_data;
        LexemeType m_type;

    public:
        Lexeme(std::string data, LexemeType type);

        auto operator<=>(const Lexeme &) const = default;

        [[nodiscard]]
        nlohmann::json to_json() const;

        [[nodiscard]]
        std::string to_string() const;

        static Lexeme from_json(const nlohmann::json &);

        inline static bool is(const Lexeme &lhs, const Lexeme &);

        [[nodiscard]]
        const std::string &get_data() const;

        [[nodiscard]]
        LexemeType get_type() const;

        const static Lexeme FN;
        const static Lexeme LCURLY;
        const static Lexeme RCURLY;
        const static Lexeme LBRACE;
        const static Lexeme RBRACE;
        const static Lexeme LBRACKET;
        const static Lexeme RBRACKET;
        const static Lexeme ADDITION;
        const static Lexeme COMMA;
        const static Lexeme SEMICOLON;
        const static Lexeme EQUALS;
    };


    using LexemeList = std::deque<Lexeme>;

} // hasha

#endif //HASHA_LEXEME_H

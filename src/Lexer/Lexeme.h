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
        OPERATOR,
        BOOLEAN_OPERATOR,
        NUMERIC_OPERATOR,
        IDENTIFIER,
        LITERAL,
        BOOLEAN_LITERAL,
        NUMERIC_LITERAL,
        STRING_LITERAL,
        SYMBOL,
        KEYWORD,
        ILLEGAL,
    };

    enum Associativity {
        Left,
        Right,
        None
    };
    enum Precedence {
        Level6 = 6,
        Level5 = 5,
        Level4 = 4,
        Level3 = 3,
        Level2 = 2,
        Level1 = 1,
        Level0 = 0
    };

    class Lexeme {
        std::string m_data;
        LexemeType m_type;
        Associativity m_associativity;
        Precedence m_precedence;

    public:

        Lexeme(
                std::string data,
                LexemeType type,
                Associativity associativity,
                Precedence precedence
        );

        Lexeme(
                std::string data,
                LexemeType type
        );


        auto operator<=>(const Lexeme &) const = default;

        [[nodiscard]]
        nlohmann::json to_json() const noexcept;

        [[nodiscard]]
        std::string to_string() const noexcept;

        [[nodiscard]]
        std::string data() const noexcept;

        [[nodiscard]]
        LexemeType get_type() const noexcept;

        [[nodiscard]]
        Precedence precedence() const noexcept;

        [[nodiscard]]
        Associativity associativity() const noexcept;
    };

    using LexemeList = std::vector<Lexeme>;

} // hasha

#endif //HASHA_LEXEME_H

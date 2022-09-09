//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXEME_H
#define HASHA_LEXEME_H

#include <string>
#include <utility>

#include "nlohmann/json.hpp"
#include "magic_enum.hpp"
#include "fmt/format.h"
#include "Span.h"

namespace hasha {

    enum class LexemeType {
        OPERATOR,
        IDENTIFIER,
        LITERAL,
        BOOLEAN_LITERAL,
        NUMERIC_LITERAL,
        STRING_LITERAL,
        SYMBOL,
        KEYWORD,
        ILLEGAL,
    };

    enum class Associativity {
        LEFT,
        RIGHT,
        NONE
    };
    enum class Precedence {
        LVL6 = 6,
        LVL5 = 5,
        LVL4 = 4,
        LVL3 = 3,
        LVL2 = 2,
        LVL1 = 1,
        NONE = 0
    };

    class Lexeme {
        std::string m_data;
        LexemeType m_type;
        Associativity m_associativity;
        Precedence m_precedence;
        Span m_span;

    public:

        bool operator==(const Lexeme &other) const;

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

        Lexeme(
                std::string data,
                LexemeType type,
                Span span
        );

        [[nodiscard]]
        nlohmann::json to_json() const noexcept;

        [[nodiscard]]
        std::string to_string() const noexcept;

        [[nodiscard]]
        std::string data() const noexcept;

        [[nodiscard]]
        LexemeType type() const noexcept;

        [[nodiscard]]
        Precedence precedence() const noexcept;

        [[nodiscard]]
        Associativity associativity() const noexcept;

        Span &span() noexcept;
    };

    using LexemeList = std::vector<Lexeme>;

} // hasha

#endif //HASHA_LEXEME_H

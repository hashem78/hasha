//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXEME_H
#define HASHA_LEXEME_H

#include "Span.h"
#include "LexerTypes.h"

namespace hasha {

    class Lexeme {
        std::string m_data;
        LexemeType m_type;
        Associativity m_associativity;
        Precedence m_precedence;
        OperatorType m_operator_type;
        Span m_span;

    public:

        bool operator==(const Lexeme &other) const;

        Lexeme(
                std::string data,
                LexemeType type,
                OperatorType operator_type,
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
        OperatorType operator_type() const noexcept;

        [[nodiscard]]
        Precedence precedence() const noexcept;

        [[nodiscard]]
        Associativity associativity() const noexcept;

        [[nodiscard]]
        const Span &span() const noexcept;

        [[nodiscard]]
        Lexeme with_span(const Span &) const noexcept;
    };

    using LexemeList = std::vector<Lexeme>;

} // hasha

#endif //HASHA_LEXEME_H

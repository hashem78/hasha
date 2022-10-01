//
// Created by mythi on 21/07/22.
//

#include <string>


#include "nlohmann/json.hpp"
#include "magic_enum.hpp"
#include "fmt/format.h"

#include "Lexeme.h"

namespace hasha {

    nlohmann::json Lexeme::to_json() const noexcept {

        if (m_type == LexemeType::OPERATOR) {
            return {
                    {"data",          m_data},
                    {"span",          m_span.to_json()},
                    {"type",          magic_enum::enum_name(m_type)},
                    {"associativity", magic_enum::enum_name(m_associativity)},
                    {"precedence",    magic_enum::enum_name(m_precedence)},
            };
        }

        return {
                {"data", m_data},
                {"span", m_span.to_json()},
                {"type", magic_enum::enum_name(m_type)}
        };
    }

    std::string Lexeme::to_string() const noexcept {

        if (m_type == LexemeType::OPERATOR) {
            return fmt::format("{} {} {} {}", magic_enum::enum_name(m_type),
                               m_data, magic_enum::enum_name(m_associativity),
                               magic_enum::enum_name(m_precedence));
        }
        return fmt::format("{} {}", magic_enum::enum_name(m_type), m_data);
    }


    std::string Lexeme::data() const noexcept {

        return m_data;
    }

    LexemeType Lexeme::type() const noexcept {

        return m_type;
    }

    Associativity Lexeme::associativity() const noexcept {

        return m_associativity;
    }

    Precedence Lexeme::precedence() const noexcept {

        return m_precedence;
    }

    Lexeme::Lexeme(
            std::string data,
            LexemeType type,
            LexOperatorType operator_type,
            Associativity associativity,
            Precedence precedence
    ) :
            m_data(std::move(data)),
            m_type(type),
            m_associativity(associativity),
            m_precedence(precedence),
            m_operator_type(operator_type),
            m_span(Span{}) {}

    Lexeme::Lexeme(std::string data, LexemeType type) :
            m_data(std::move(data)),
            m_type(type),
            m_associativity(Associativity::NONE),
            m_precedence(Precedence::NONE),
            m_operator_type(),
            m_span(Span{}) {}

    Lexeme::Lexeme(
            std::string data,
            LexemeType type,
            LexLitrealType litreal_type
    ) :
            m_data(std::move(data)),
            m_type(type),
            m_litreal_type(litreal_type),
            m_associativity(Associativity::NONE),
            m_precedence(Precedence::NONE),
            m_operator_type(),
            m_span(Span{}) {

    }

    Lexeme::Lexeme(
            std::string data,
            LexemeType type,
            LexLitrealType op,
            Span span
    ) :
            m_data(std::move(data)),
            m_type(type),
            m_litreal_type(op),
            m_associativity(Associativity::NONE),
            m_precedence(Precedence::NONE),
            m_operator_type(),
            m_span(span) {}


    const Span &Lexeme::span() const noexcept {

        return m_span;
    }

    Lexeme Lexeme::with_span(const Span &span) const noexcept {

        Lexeme lexeme = *this;
        lexeme.m_span = span;

        return lexeme;
    }

    bool Lexeme::operator==(const Lexeme &other) const {

        return std::tie(m_data, m_type, m_precedence, m_associativity) ==
               std::tie(other.m_data, other.m_type, other.m_precedence, other.m_associativity);
    }

    LexOperatorType Lexeme::operator_type() const noexcept {

        return m_operator_type;
    }

    LexLitrealType Lexeme::litreal_type() const noexcept {

        return m_litreal_type;
    }


} // hasha
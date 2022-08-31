//
// Created by mythi on 21/07/22.
//

#include "Lexeme.h"

namespace hasha {

    nlohmann::json Lexeme::to_json() const noexcept {

        if (m_type == LexemeType::OPERATOR) {
            return {
                    {"data",          m_data},
                    {"type",          magic_enum::enum_name(m_type)},
                    {"associativity", magic_enum::enum_name(m_associativity)},
                    {"precedence",    magic_enum::enum_name(m_precedence)},
            };
        }

        return {{"data", m_data},
                {"type", magic_enum::enum_name(m_type)}};
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

    LexemeType Lexeme::get_type() const noexcept {

        return m_type;
    }

    Associativity Lexeme::associativity() const noexcept {

        return m_associativity;
    }

    Precedence Lexeme::precedence() const noexcept {

        return m_precedence;
    }

    Lexeme::Lexeme(std::string data, LexemeType type, Associativity associativity, Precedence precedence) :
            m_data(std::move(data)),
            m_type(type),
            m_associativity(associativity),
            m_precedence(precedence)
    {}

    Lexeme::Lexeme(std::string data, LexemeType type) :
            m_data(std::move(data)),
            m_type(type),
            m_associativity(Associativity::None),
            m_precedence(Precedence::Level0) {}
} // hasha
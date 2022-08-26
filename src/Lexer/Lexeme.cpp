//
// Created by mythi on 21/07/22.
//

#include "Lexeme.h"

namespace hasha {

    nlohmann::json Lexeme::to_json() const {

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

    std::string Lexeme::to_string() const {

        if (m_type == LexemeType::OPERATOR) {
            return fmt::format("{} {} {} {}", magic_enum::enum_name(m_type),
                               m_data, magic_enum::enum_name(m_associativity),
                               magic_enum::enum_name(m_precedence));
        }
        return fmt::format("{} {}", magic_enum::enum_name(m_type), m_data);
    }


    std::string Lexeme::get_data() const {

        return m_data;
    }

    LexemeType Lexeme::get_type() const {

        return m_type;
    }

    Associativity Lexeme::get_associativity() const {

        return m_associativity;
    }

    Precedence Lexeme::get_precedence() const {

        return m_precedence;
    }

    bool Lexeme::is_string() const {

        return m_isstring;
    }

    bool Lexeme::is_boolean() const {

        return m_isboolean;
    }

    bool Lexeme::is_numeric_operator() const {

        return m_is_numeric_operator;
    }

    bool Lexeme::is_boolean_operator() const {

        return m_is_boolean_operator;
    }

    int Lexeme::get_id() const noexcept {

        return m_id;
    }

    int Lexeme::id_counter = 0;
} // hasha
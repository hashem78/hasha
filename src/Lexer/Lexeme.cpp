//
// Created by mythi on 21/07/22.
//

#include "Lexeme.h"

namespace hasha {


    Lexeme::Lexeme(std::string data, LexemeType type, Associativity associativity, Precedence precedence) : m_data(
            std::move(data)), m_type(type), m_associativity(associativity), m_precedence(precedence) {}

    nlohmann::json Lexeme::to_json() const {

        if (m_type == LexemeType::Operator) {
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

        if (m_type == LexemeType::Operator) {
            fmt::format("{} {} {} {}", magic_enum::enum_name(m_type),
                        m_data, magic_enum::enum_name(m_associativity),
                        magic_enum::enum_name(m_precedence));
        }
        return fmt::format("{} {}", magic_enum::enum_name(m_type), m_data);
    }

    const Lexeme Lexeme::FN{"fn", LexemeType::Keyword};
    const Lexeme Lexeme::LCURLY{"{", LexemeType::Symbol};
    const Lexeme Lexeme::RCURLY{"}", LexemeType::Symbol};
    const Lexeme Lexeme::LPAREN{"(", LexemeType::Symbol};
    const Lexeme Lexeme::RPAREN{")", LexemeType::Symbol};
    const Lexeme Lexeme::LBRACKET{"[", LexemeType::Symbol};
    const Lexeme Lexeme::RBRACKET{"]", LexemeType::Symbol};
    const Lexeme Lexeme::COMMA{",", LexemeType::Symbol};
    const Lexeme Lexeme::SEMICOLON{";", LexemeType::Symbol};
    const Lexeme Lexeme::EQUALS{"=", LexemeType::Operator, Associativity::Right, Precedence::Level1};
    const Lexeme Lexeme::HYPHEN{"-", LexemeType::Operator, Associativity::Left, Precedence::Level3};
    const Lexeme Lexeme::ADDITION{"+", LexemeType::Operator, Associativity::Left, Precedence::Level3};
    const Lexeme Lexeme::FSLASH{"/", LexemeType::Operator, Associativity::Left, Precedence::Level5};
    const Lexeme Lexeme::ASTERISK{"*", LexemeType::Operator, Associativity::Left, Precedence::Level6};


    const std::string &Lexeme::get_data() const {

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


} // hasha
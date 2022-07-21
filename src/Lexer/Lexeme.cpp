//
// Created by mythi on 21/07/22.
//

#include "Lexeme.h"

namespace hasha {


    Lexeme::Lexeme(std::string data, LexemeType type) : m_data(std::move(data)), m_type(type) {}

    nlohmann::json Lexeme::to_json() const {

        return {{"data", m_data},
                {"type", magic_enum::enum_name(m_type)}};
    }

    Lexeme Lexeme::from_json(const nlohmann::json &json) {

        return {
                json["data"],
                magic_enum::enum_cast<hasha::LexemeType>(std::string{json["type"]}).value()
        };
    }

    std::string Lexeme::to_string() const {

        return fmt::format("{} {}", magic_enum::enum_name(m_type), m_data);
    }

    const Lexeme Lexeme::FN{"fn", LexemeType::Keyword};
    const Lexeme Lexeme::LCURLY{"{", LexemeType::Symbol};
    const Lexeme Lexeme::RCURLY{"}", LexemeType::Symbol};
    const Lexeme Lexeme::LBRACE{"(", LexemeType::Symbol};
    const Lexeme Lexeme::RBRACE{")", LexemeType::Symbol};
    const Lexeme Lexeme::LBRACKET{"[", LexemeType::Symbol};
    const Lexeme Lexeme::RBRACKET{"]", LexemeType::Symbol};
    const Lexeme Lexeme::COMMA{",", LexemeType::Symbol};
    const Lexeme Lexeme::ADDITION{"+", LexemeType::Operator};


    bool Lexeme::is(const Lexeme &lhs, const Lexeme &rhs) {
        return lhs == rhs;
    }

    const std::string &Lexeme::get_data() const {

        return m_data;
    }

    LexemeType Lexeme::get_type() const {

        return m_type;
    }


} // hasha
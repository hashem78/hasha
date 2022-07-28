//
// Created by mythi on 28/07/22.
//

#include "Literal.h"

namespace hasha {
    Literal::Literal(std::string literal, bool isstring) noexcept: m_literal(std::move(literal)), m_isstring(isstring) {

    }

    Literal::LiteralPtr Literal::create(std::string literal, bool isstring) {

        return std::shared_ptr<Literal>(new Literal(std::move(literal), isstring));
    }

    nlohmann::json Literal::to_json() const {

        auto json = nlohmann::json();
        json["litreal"] = m_literal;

        if (m_isstring) {
            json["token_type"] = "StringLiteral";
        } else {
            json["token_type"] = "Literal";
        }

        return json;
    }

    std::string Literal::to_string() const {

        if (m_isstring) {
            return fmt::format("StringLiteral {}", m_literal);
        }
        return fmt::format("Literal {}", m_literal);
    }

    const std::string &Literal::get_literal() const noexcept {

        return m_literal;
    }

    void Literal::set_literal(const std::string &literal) noexcept {

        Literal::m_literal = literal;
    }

    bool Literal::is_string() const {

        return m_isstring;
    }
} // hasha
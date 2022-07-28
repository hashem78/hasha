//
// Created by mythi on 28/07/22.
//

#include "Literal.h"

namespace hasha {
    Literal::Literal(std::string literal) noexcept: m_literal(std::move(literal)) {

    }

    Literal::LiteralPtr Literal::create(std::string literal) {

        return std::shared_ptr<Literal>(new Literal(std::move(literal)));
    }

    nlohmann::json Literal::to_json() const {

        return {
                {"token_type", "Literal"},
                {"literal",       m_literal}
        };
    }

    std::string Literal::to_string() const {

        return fmt::format("Literal {}", m_literal);
    }

    const std::string &Literal::get_literal() const noexcept {

        return m_literal;
    }

    void Literal::set_literal(const std::string &literal) noexcept {

        Literal::m_literal = literal;
    }
} // hasha
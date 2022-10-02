//
// Created by mythi on 01/10/22.
//

#include "Literal.h"

namespace hasha {
    Literal::Literal(
            LiteralType type,
            std::string literal,
            Span span,
            int scope_id
    ) :
            m_type(type),
            m_literal(std::move(literal)),
            TokenBase(span, scope_id, "Literal"sv) {

    }

    const std::string &Literal::literal() const noexcept {

        return m_literal;
    }

    LiteralType Literal::type() const {

        return m_type;
    }
} // hasha
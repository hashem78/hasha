//
// Created by mythi on 26/08/22.
//
#include "Literal.h"

namespace hasha {

    Literal::Literal(
            Type  type,
            std::string literal,
            const Span &span,
            int scope_id
    ) :
            m_type(std::move(type)),
            m_literal(std::move(literal)),
            Token(span, scope_id) {

    }

    const std::string &Literal::get_literal() const noexcept {

        return m_literal;
    }

    const Type &Literal::type() const {

        return m_type;
    }
}
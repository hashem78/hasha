//
// Created by mythi on 26/08/22.
//
#include "Literal.h"

namespace hasha {

    Literal::Literal(std::string literal, const Span &span) :
            m_literal(std::move(literal)),
            Token(span) {

    }

    const std::string &Literal::get_literal() const noexcept {

        return m_literal;
    }
}
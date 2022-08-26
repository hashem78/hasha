//
// Created by mythi on 26/08/22.
//
#include "Literal.h"

namespace hasha {

    Literal::Literal(std::string literal) : m_literal(std::move(literal)){

    }

    const std::string &Literal::get_literal() const noexcept {

        return m_literal;
    }
}
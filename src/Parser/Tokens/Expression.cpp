//
// Created by mythi on 01/10/22.
//

#include "Expression.h"

namespace hasha {
    Expression::Expression(
            TokenList expr,
            Span span,
            int scope_id
    ) :
            m_expression(std::move(expr)),
            TokenBase(span, scope_id, "Expression"sv) {
    }

    bool Expression::empty() const noexcept {

        return m_expression.empty();
    }

    const TokenList &Expression::expression() const noexcept {

        return m_expression;
    }

} // hasha
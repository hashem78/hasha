//
// Created by mythi on 04/10/22.
//

#include "ReturnToken.h"

namespace hasha {
    ReturnToken::ReturnToken(
            Box<Expression> expression,
            Span span,
            int scope_id
    ) noexcept:
            m_expression(std::move(expression)),
            TokenBase(span, scope_id, "ReturnToken") {

    }

    const Box<Expression> &ReturnToken::expression() const noexcept {

        return m_expression;
    }
} // hasha
//
// Created by mythi on 01/10/22.
//

#include "Assignment.h"

namespace hasha {
    Assignment::Assignment(
            Box<Identifier> assignee,
            Box<Expression> expression,
            Span span,
            int scope_id
    ) noexcept:
            m_assignee(std::move(assignee)),
            m_expression(std::move(expression)),
            TokenBase(span, scope_id, "Assignment"sv) {

    }

    const Expression &Assignment::expression() const noexcept {

        return *m_expression;
    }

    const Identifier &Assignment::assignee() const noexcept {

        return *m_assignee;
    }
} // hasha
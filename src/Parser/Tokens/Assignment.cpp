//
// Created by mythi on 01/10/22.
//

#include "Assignment.h"
#include "TokenBase.h"

namespace hasha {
  Assignment::Assignment(
    Box<Identifier> assignee,
    Box<Expression> expression,
    Span span,
    uuid scope_id
  ) noexcept
      : m_assignee(std::move(assignee)),
        m_expression(std::move(expression)),
        CONSTRUCT_DETAILS(Assignment) {
  }

  const Box<Expression> &Assignment::expression() const noexcept {

    return m_expression;
  }

  const Box<Identifier> &Assignment::assignee() const noexcept {

    return m_assignee;
  }
}// namespace hasha
//
// Created by mythi on 04/10/22.
//

#include "ReturnToken.h"
#include "TokenBase.h"

namespace hasha {
  ReturnToken::ReturnToken(
    Box<Expression> expression,
    Span span,
    uuid scope_id
  ) noexcept
      : m_expression(std::move(expression)),
        CONSTRUCT_DETAILS(ReturnToken) {
  }

  const Box<Expression> &ReturnToken::expression() const noexcept {

    return m_expression;
  }
}// namespace hasha
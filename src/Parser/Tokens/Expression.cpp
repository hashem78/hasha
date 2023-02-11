//
// Created by mythi on 01/10/22.
//

#include "Expression.h"

namespace hasha {
  Expression::Expression(
    std::vector<Token> expr,
    Span span,
    uuid scope_id
  )
      : m_expression(std::move(expr)),
        CONSTRUCT_DETAILS(Expression) {
  }

  bool Expression::empty() const noexcept {

    return m_expression.empty();
  }

  const std::vector<Token> &Expression::expression() const noexcept {

    return m_expression;
  }

}// namespace hasha
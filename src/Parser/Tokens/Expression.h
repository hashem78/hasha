//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_EXPRESSION_H
#define HASHA_EXPRESSION_H

#include "Token.h"
#include "TokenBase.h"

namespace hasha {

  class [[nodiscard]] Expression final {
    std::vector<Token> m_expression;
    DEFINE_DETAILS()

   public:
    Expression(
      std::vector<Token> expr,
      Span span,
      uuid scope_id
    );

    [[nodiscard]] bool empty() const noexcept;

    [[nodiscard]] const std::vector<Token> &expression() const noexcept;
  };

  using BoxedExpression = Box<Expression>;
  using BoxedExpressionList = std::vector<BoxedExpression>;
}// namespace hasha

#endif//HASHA_EXPRESSION_H
//
// Created by mythi on 01/10/22.
//

#include "Operator.h"

namespace hasha {

  Operator::Operator(
    OperatorType type,
    std::string op,
    Span span,
    uuid scope_id
  )
      : m_type(type),
        m_op(std::move(op)),
        CONSTRUCT_DETAILS(Operator) {
  }

  const std::string &Operator::operation() const noexcept {

    return m_op;
  }

  OperatorType Operator::type() const noexcept {

    return m_type;
  }
}// namespace hasha
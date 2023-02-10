//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_OPERATOR_H
#define HASHA_OPERATOR_H

#include "Box.h"
#include "OperatorType.h"
#include "TokenBase.h"

namespace hasha {

  class Operator : public TokenBase {
   protected:
    OperatorType m_type;
    std::string m_op;

   public:
    Operator(
      OperatorType type,
      std::string op,
      Span span,
      int scope_id
    );

    [[nodiscard]] const std::string &operation() const noexcept;

    [[nodiscard]] OperatorType type() const noexcept;
  };

  using BoxedOperator = Box<Operator>;
}// namespace hasha

#endif//HASHA_OPERATOR_H

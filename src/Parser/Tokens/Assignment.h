//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_ASSIGNMENT_H
#define HASHA_ASSIGNMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class Assignment : public TokenBase {

    Box<Identifier> m_assignee;
    Box<Expression> m_expression;

   public:
    Assignment(
      Box<Identifier> assignee,
      Box<Expression> expression,
      Span span,
      int scope_id
    ) noexcept;


    [[nodiscard]] const Box<Expression> &expression() const noexcept;

    [[nodiscard]] const Box<Identifier> &assignee() const noexcept;
  };

  using BoxedAssignment = Box<Assignment>;
}// namespace hasha

#endif//HASHA_ASSIGNMENT_H

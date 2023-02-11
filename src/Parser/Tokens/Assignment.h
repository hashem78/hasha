//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_ASSIGNMENT_H
#define HASHA_ASSIGNMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"


namespace hasha {

  class [[nodiscard]] Assignment final {

    Box<Identifier> m_assignee;
    Box<Expression> m_expression;

    DEFINE_DETAILS()

   public:
    Assignment(
      Box<Identifier> assignee,
      Box<Expression> expression,
      Span span,
      uuid scope_id
    ) noexcept;


    [[nodiscard]] const Box<Expression> &expression() const noexcept;

    [[nodiscard]] const Box<Identifier> &assignee() const noexcept;
  };

  using BoxedAssignment = Box<Assignment>;
}// namespace hasha

#endif//HASHA_ASSIGNMENT_H

//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_IFSTATEMENT_H
#define HASHA_IFSTATEMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class [[nodiscard]] IfStatement final {

    Box<Expression> m_condition;
    Box<Block> m_block;

    DEFINE_DETAILS()
   public:
    IfStatement(
      Box<Expression> condition,
      Box<Block> block,
      Span span,
      uuid scope_id
    ) noexcept;

    [[nodiscard]] const Box<Expression> &condition() const noexcept;

    [[nodiscard]] const Box<Block> &block() const noexcept;
  };

  using BoxedIfStatement = Box<IfStatement>;

}// namespace hasha

#endif//HASHA_IFSTATEMENT_H

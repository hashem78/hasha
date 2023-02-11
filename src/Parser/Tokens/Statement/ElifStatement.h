//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_ELIFSTATEMENT_H
#define HASHA_ELIFSTATEMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class [[nodiscard]] ElifStatement final {
    Box<Expression> m_condition;
    Box<Block> m_block;

    DEFINE_DETAILS()
   public:
    ElifStatement(
      Box<Expression> condition,
      Box<Block> block,
      Span span,
      uuid scope_id
    ) noexcept;

    [[nodiscard]] const Box<Expression> &condition() const noexcept;

    [[nodiscard]] const Box<Block> &block() const noexcept;
  };

  using BoxedElifStatement = Box<ElifStatement>;
}// namespace hasha

#endif//HASHA_ELIFSTATEMENT_H

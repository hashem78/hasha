//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_ELIFSTATEMENT_H
#define HASHA_ELIFSTATEMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class ElifStatement : public TokenBase {
    Box<Expression> m_condition;
    Box<Block> m_block;

   public:
    ElifStatement(
      Box<Expression> condition,
      Box<Block> block,
      const Span &span,
      int scope_id
    ) noexcept;

    [[nodiscard]] const Box<Expression> &condition() const noexcept;

    [[nodiscard]] const Box<Block> &block() const noexcept;
  };

  using BoxedElifStatement = Box<ElifStatement>;
}// namespace hasha

#endif//HASHA_ELIFSTATEMENT_H

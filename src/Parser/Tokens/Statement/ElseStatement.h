//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_ELSESTATEMENT_H
#define HASHA_ELSESTATEMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class ElseStatement : public TokenBase {

    Box<Block> m_block;

   public:
    ElseStatement(
      Box<Block> block,
      Span span,
      int scope_id
    ) noexcept;

    [[nodiscard]] const Box<Block> &block() const noexcept;
  };

  using BoxedElseStatement = Box<ElseStatement>;
}// namespace hasha

#endif//HASHA_ELSESTATEMENT_H

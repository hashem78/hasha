//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_ELSESTATEMENT_H
#define HASHA_ELSESTATEMENT_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class [[nodiscard]] ElseStatement final {

    Box<Block> m_block;

    DEFINE_DETAILS()
   public:
    ElseStatement(
      Box<Block> block,
      Span span,
      uuid scope_id
    ) noexcept;

    [[nodiscard]] const Box<Block> &block() const noexcept;
  };

  using BoxedElseStatement = Box<ElseStatement>;
}// namespace hasha

#endif//HASHA_ELSESTATEMENT_H

//
// Created by mythi on 02/10/22.
//

#include "ElseStatement.h"

namespace hasha {
  ElseStatement::ElseStatement(
    Box<Block> block,
    Span span,
    uuid scope_id
  ) noexcept
      : m_block(std::move(block)),
        CONSTRUCT_DETAILS(ElseStatement) {
  }

  const Box<Block> &ElseStatement::block() const noexcept {

    return m_block;
  }
}// namespace hasha
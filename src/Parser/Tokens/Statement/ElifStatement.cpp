//
// Created by mythi on 02/10/22.
//

#include "ElifStatement.h"

namespace hasha {
  ElifStatement::ElifStatement(
    Box<Expression> condition,
    Box<Block> block,
    Span span,
    uuid scope_id
  ) noexcept
      : m_condition(std::move(condition)),
        m_block(std::move(block)),
        CONSTRUCT_DETAILS(ElifStatement) {
  }

  const Box<Expression> &ElifStatement::condition() const noexcept {

    return m_condition;
  }

  const Box<Block> &ElifStatement::block() const noexcept {

    return m_block;
  }
}// namespace hasha
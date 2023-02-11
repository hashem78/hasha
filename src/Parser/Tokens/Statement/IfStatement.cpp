//
// Created by mythi on 02/10/22.
//

#include "IfStatement.h"

namespace hasha {
  IfStatement::IfStatement(
    Box<Expression> condition,
    Box<Block> block,
    Span span,
    uuid scope_id
  ) noexcept
      : m_condition(std::move(condition)),
        m_block(std::move(block)),
        CONSTRUCT_DETAILS(IfStatement) {
  }

  const Box<Expression> &IfStatement::condition() const noexcept {

    return m_condition;
  }

  const Box<Block> &IfStatement::block() const noexcept {

    return m_block;
  }

}// namespace hasha
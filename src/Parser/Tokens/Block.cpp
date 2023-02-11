//
// Created by mythi on 01/10/22.
//

#include "Block.h"
#include "TokenBase.h"

namespace hasha {
  Block::Block(
    std::vector<Token> tokens,
    Span span,
    uuid scope_id,
    bool contains_return
  ) noexcept
      : m_tokens(std::move(tokens)),
        m_contains_return(contains_return),
        CONSTRUCT_DETAILS(Block) {
  }

  const std::vector<Token> &Block::tokens() const noexcept {

    return m_tokens;
  }

  bool Block::contains_return() const noexcept {

    return m_contains_return;
  }
}// namespace hasha
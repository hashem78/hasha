//
// Created by mythi on 01/10/22.
//

#include "Block.h"

namespace hasha {
  Block::Block(
    TokenList tokens,
    Span span,
    int scope_id,
    bool contains_return
  ) noexcept
      : m_tokens(std::move(tokens)),
        m_contains_return(contains_return),
        TokenBase(span, scope_id, "Block"sv) {
  }

  const TokenList &Block::tokens() const noexcept {

    return m_tokens;
  }

  bool Block::contains_return() const noexcept {

    return m_contains_return;
  }
}// namespace hasha
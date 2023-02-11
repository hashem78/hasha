//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_BLOCK_H
#define HASHA_BLOCK_H

#include "Box.h"
#include "Token.h"
#include "TokenBase.h"

namespace hasha {

  class [[nodiscard]] Block final {
    std::vector<Token> m_tokens;
    bool m_contains_return;

    DEFINE_DETAILS()

   public:
    Block(
      std::vector<Token> tokens,
      Span span,
      uuid scope_id,
      bool contains_return = false
    ) noexcept;

    [[nodiscard]] const std::vector<Token> &tokens() const noexcept;

    [[nodiscard]] bool contains_return() const noexcept;
  };

  using BoxedBlock = Box<Block>;
}// namespace hasha

#endif//HASHA_BLOCK_H

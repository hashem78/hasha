//
// Created by mythi on 01/10/22.
//

#include "Block.h"

namespace hasha {
    Block::Block(
            TokenList tokens,
            Span span,
            int scope_id
    ) noexcept:
            m_tokens(std::move(tokens)),
            TokenBase(span, scope_id) {

    }

    const TokenList &Block::tokens() const noexcept {

        return m_tokens;
    }
} // hasha
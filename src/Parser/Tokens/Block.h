//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_BLOCK_H
#define HASHA_BLOCK_H

#include "TokenBase.h"
#include "TokenForwards.h"
#include "Token.h"

namespace hasha {

    class Block : public TokenBase {
        TokenList m_tokens;
        bool m_contains_return;
    public:
        Block(
                TokenList tokens,
                Span span,
                int scope_id,
                bool contains_return = false
        ) noexcept;

        [[nodiscard]]
        const TokenList &tokens() const noexcept;

        [[nodiscard]]
        bool contains_return() const noexcept;
    };

    using BoxedBlock = Box<Block>;
} // hasha

#endif //HASHA_BLOCK_H

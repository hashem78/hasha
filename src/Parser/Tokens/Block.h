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

    public:
        Block(
                TokenList tokens,
                Span span,
                int scope_id
        ) noexcept;

        [[nodiscard]]
        const TokenList &tokens() const noexcept;
    };

    using BoxedBlock = Box<Block>;
} // hasha

#endif //HASHA_BLOCK_H

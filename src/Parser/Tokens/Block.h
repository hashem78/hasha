//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_BLOCK_H
#define HASHA_BLOCK_H

#include <memory>
#include <deque>

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Block : public Token {
        TokenListPtr m_tokens;

    public:
        using BlockPtr = std::shared_ptr<Block>;

        explicit Block(TokenListPtr m_tokens);
        static BlockPtr create(TokenListPtr m_tokens);

        Block& add(TokenPtr token);

        [[nodiscard]]
        const TokenList &get_tokens() const;

        void set_tokens(TokenListPtr tokens);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

    };

} // hasha

#endif //HASHA_BLOCK_H

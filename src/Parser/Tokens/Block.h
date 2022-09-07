//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_BLOCK_H
#define HASHA_BLOCK_H

#include <memory>
#include <deque>

#include "Token.h"
#include "fmt/format.h"
#include "Tokens/Expression/Expression.h"

namespace hasha {

    class Block : public Token {
        TokenListPtr m_tokens;
        Scope::Ptr m_scope;

    public:
        explicit Block(TokenListPtr tokens, const Span &span);

        explicit Block(TokenListPtr tokens, const Span &span, Scope::Ptr scope);

        using Ptr = std::unique_ptr<Block>;

        static Ptr create(TokenListPtr tokens, const Span &span);

        [[nodiscard]]
        TokenListPtr get_tokens() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

        void interpret(Scope::Ptr scope) override;

        Scope::Ptr scope();
    };

} // hasha

#endif //HASHA_BLOCK_H

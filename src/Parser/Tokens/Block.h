//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_BLOCK_H
#define HASHA_BLOCK_H

#include "Token.h"
#include "fmt/format.h"
#include "Tokens/Expression/Expression.h"

namespace hasha {

    class Block : public Token {
        TokenList m_tokens;
        Scope::Ptr m_scope;

    public:
        explicit Block(TokenList tokens, const Span &span);

        explicit Block(TokenList tokens, const Span &span, Scope::Ptr scope);

        using Ptr = std::unique_ptr<Block>;

        static Ptr create(TokenList tokens, const Span &span);

        [[nodiscard]]
        const TokenList& get_tokens() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

        void interpret(Scope::Ptr scope) override;

        Scope::Ptr scope();
    };

} // hasha

#endif //HASHA_BLOCK_H

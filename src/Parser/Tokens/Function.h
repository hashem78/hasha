//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_FUNCTION_H
#define HASHA_FUNCTION_H

#include "Token.h"
#include "Block.h"
#include "Parameter.h"
#include "Tokens/Type/Type.h"
#include "Tokens/Expression/Expression.h"

namespace hasha {
    class Block;

    class Function : public Token {
        TokenList m_parameters;
    public:
        ErrorOr<void> interpret(const ScopeTree &scope_tree) override;

    private:
        Block::Ptr m_block;
        Type::Ptr m_return_type;
        Identifier m_name;

    public:

        Function(
                TokenList parameters,
                Block::Ptr block,
                Identifier name,
                Type::Ptr return_type,
                const Span &span,
                int scope_id
        );

        using Ptr = std::unique_ptr<Function>;

        static Ptr create(
                TokenList parameters,
                Block::Ptr block,
                Identifier name,
                Type::Ptr return_type,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        const TokenList &get_parameters() const;

        [[nodiscard]]
        const class Block *get_block() const;

        [[nodiscard]]
        Identifier get_name() const;

        [[nodiscard]]
        const Type *get_return_type() const;

    };

} // hasha

#endif //HASHA_FUNCTION_H

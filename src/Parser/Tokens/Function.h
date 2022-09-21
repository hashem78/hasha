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

        Block::Ptr m_block;
        ParameterList m_parameters;
        Type::Ptr m_return_type;
        Identifier m_name;

    public:

        Function(
                ParameterList parameters,
                Block::Ptr block,
                Identifier name,
                Type::Ptr return_type,
                const Span &span,
                int scope_id
        );

        using Ptr = std::unique_ptr<Function>;

        static Ptr create(
                ParameterList parameters,
                Block::Ptr block,
                Identifier name,
                Type::Ptr return_type,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        const Identifier &name() const;

        [[nodiscard]]
        const Type &return_type() const;

        [[nodiscard]]
        const ParameterList &parameters() const;

        [[nodiscard]]
        int number_of_parameters() const;

        [[nodiscard]]
        const class Block &block() const;

    };

} // hasha

#endif //HASHA_FUNCTION_H

//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_IFSTATEMENT_H
#define HASHA_IFSTATEMENT_H

#include "Token.h"
#include "Block.h"
#include "Tokens/Expression/Expression.h"

namespace hasha {

    class IfStatement : public Token {

        Expression::Ptr condition;
        Block::Ptr block;
    public:
        using Ptr = std::unique_ptr<IfStatement>;

        IfStatement(
                Expression::Ptr condition,
                Block::Ptr block,
                const Span &span,
                int scope_id
        );

        static Ptr create(
                Expression::Ptr condition,
                Block::Ptr block,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        const Expression& get_condition() const;

        [[nodiscard]]
        const Block& get_block() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

    };


} // hasha

#endif //HASHA_IFSTATEMENT_H

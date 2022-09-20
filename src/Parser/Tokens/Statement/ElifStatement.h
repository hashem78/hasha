//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_ELIFSTATEMENT_H
#define HASHA_ELIFSTATEMENT_H

#include "Token.h"
#include "Block.h"
#include "Expression/Expression.h"

namespace hasha {

    class ElifStatement : public Token {
        Expression::Ptr m_condition;
        Block::Ptr m_block;

    public:

        ElifStatement(
                Expression::Ptr condition,
                Block::Ptr block,
                const Span &span,
                int scope_id
        );

        using Ptr = std::unique_ptr<ElifStatement>;

        static ElifStatement::Ptr create(
                Expression::Ptr condition,
                Block::Ptr block,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        const Expression &condition() const;

        [[nodiscard]]
        const Block &block() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ELIFSTATEMENT_H

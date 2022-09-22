//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_ASSIGNMENT_H
#define HASHA_ASSIGNMENT_H

#include "Tokens/Expression/Expression.h"
#include "Identifier.h"

namespace hasha {

    class Assignment : public Token {

        Identifier::Ptr m_assignee;
        Expression::Ptr m_expression;

    public:
        using Ptr = std::unique_ptr<Assignment>;

        explicit Assignment(
                Identifier::Ptr assignee,
                Expression::Ptr expression,
                const Span &span,
                int scope_id
        );

        static Ptr create(
                Identifier::Ptr assignee,
                Expression::Ptr expression,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        const Expression &expression() const;

        [[nodiscard]]
        const Identifier &assignee() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ASSIGNMENT_H

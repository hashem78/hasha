//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_ASSIGNMENT_H
#define HASHA_ASSIGNMENT_H

#include "Tokens/Expression/Expression.h"

namespace hasha {

    class Assignment : public Token {

        Expression::Ptr expression;
    public:
        using Ptr = std::unique_ptr<Assignment>;

        explicit Assignment(Expression::Ptr expression, const Span &span, int scope_id);

        static Ptr create(Expression::Ptr expression, const Span &span, int scope_id);

        [[nodiscard]]
        std::string evaluate(const Scope& scope) const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ASSIGNMENT_H

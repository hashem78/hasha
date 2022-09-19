//
// Created by mythi on 03/09/22.
//

#ifndef HASHA_RETURNEXPRESSION_H
#define HASHA_RETURNEXPRESSION_H

#include "Expression.h"

namespace hasha {

    class ReturnExpression : public Expression {
    public:
        explicit ReturnExpression(TokenList expr, const Span &span, int scope_id);

        using Ptr = std::unique_ptr<ReturnExpression>;

        static Ptr create(TokenList expr, const Span &span, int scope_id);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };


} // hasha

#endif //HASHA_RETURNEXPRESSION_H

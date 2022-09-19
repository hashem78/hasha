//
// Created by mythi on 03/09/22.
//
#include "ReturnExpression.h"

namespace hasha {

    nlohmann::json ReturnExpression::to_json() const {

        auto json = Expression::to_json();
        json["token_type"] = "ReturnExpression";
        return json;
    }

    ReturnExpression::ReturnExpression(
            TokenList expr,
            const Span &span,
            int scope_id
    ) : Expression(std::move(expr), span, scope_id) {

    }

    ReturnExpression::Ptr ReturnExpression::create(
            TokenList expr,
            const Span &span, int scope_id
    ) {

        return std::make_unique<ReturnExpression>(std::move(expr), span, scope_id);
    }
}
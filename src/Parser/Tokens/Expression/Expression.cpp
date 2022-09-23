//
// Created by mythi on 01/09/22.
//

#include "Expression.h"

namespace hasha {
    nlohmann::json Expression::to_json() const {

        return {
                {"token_type", "Expression"},
                {"expression", token_list_to_json(expression)},
                {"span",       m_span.to_json()}
        };
    }

    Expression::Ptr Expression::create(TokenList expr, const Span &span, int scope_id) {

        return std::make_unique<Expression>(std::move(expr), span, scope_id);
    }

    Expression::Expression(
            TokenList expr,
            const Span &span, int scope_id
    ) :
            expression(std::move(expr)),
            Token(span, scope_id) {
    }

    bool Expression::empty() const {

        return expression.empty();
    }

    const TokenList &Expression::expression_tokens() const {

        return expression;
    }

    nlohmann::json expression_list_to_json(const ExpressionList &expression_list) {

        auto arr = nlohmann::json::array();
        for (const auto &expr: expression_list) {
            arr.push_back(expr->to_json());
        }
        return arr;
    }
} // hasha
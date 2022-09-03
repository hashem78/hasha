//
// Created by mythi on 01/09/22.
//

#include "Expression.h"

namespace hasha {
    nlohmann::json Expression::to_json() const {

        return {
                {"token_type", "Expression"},
                {"expression", token_list_to_json(expression.get())},
                {"span",m_span.to_json()}
        };
    }

    Expression::Ptr Expression::create(TokenListPtr expr, const Span &span) {

        return std::make_unique<Expression>(std::move(expr), span);
    }

    const TokenList *Expression::get_expression() const {

        return expression.get();
    }

    Expression::Expression(
            TokenListPtr expr,
            const Span &span
    ) :
            expression(std::move(expr)),
            Token(span) {
    }

    ExpressionListPtr create_expression_list() {

        return std::make_unique<ExpressionList>();
    }

    nlohmann::json expression_list_to_json(const ExpressionList *expression_list) {

        auto arr = nlohmann::json::array();
        for (const auto &expr: *expression_list) {
            arr.push_back(expr->to_json());
        }
        return arr;
    }
} // hasha
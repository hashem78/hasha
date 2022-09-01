//
// Created by mythi on 01/09/22.
//

#include "Expression.h"

namespace hasha {
    nlohmann::json Expression::to_json() const {

        return token_list_to_json(expression.get());
    }

    Expression::Ptr Expression::create(TokenListPtr expr) {

        return std::make_unique<Expression>(std::move(expr));
    }

    const TokenList *Expression::get_expression() const {

        return expression.get();
    }

    Expression::Expression(TokenListPtr expr) : expression(std::move(expr)) {

    }

    ExpressionListPtr create_expression_list() {
        return std::make_unique<ExpressionList>();
    }

    nlohmann::json expression_list_to_json(const ExpressionList *expression_list) {
        auto arr = nlohmann::json::array();
        for(const auto& expr : *expression_list){
            arr.push_back(expr->to_json());
        }
        return arr;
    }
} // hasha
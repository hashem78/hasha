//
// Created by mythi on 22/07/22.
//

#include "ArrayExpression.h"

#include <utility>

namespace hasha {
    nlohmann::json ArrayExpression::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "ArrayExpression";
        auto expression_list_json = nlohmann::json();
        for (const auto &expression: *expressions) {
            expression_list_json.push_back(expression->to_json());
        }
        json["expressions"] = expression_list_json;
        return json;
    }

    std::string ArrayExpression::to_string() const {

        std::string str = "ArrayExpression\n";
        for (const auto &expression: *expressions) {
            str += fmt::format("- {}\n", expression->to_string());
        }

        return str;
    }

    ArrayExpression::ArrayExpression(ExpressionListPtr m_expressions) :
            expressions(std::move(m_expressions)) {}

    ArrayExpression::ArrayExpressionPtr ArrayExpression::create(ExpressionListPtr expressions) {

        return std::shared_ptr<ArrayExpression>(new ArrayExpression(std::move(expressions)));
    }

    ArrayExpression &ArrayExpression::add_expression(ExpressionPtr expression) {

        expressions->push_back(std::move(expression));
        return *this;
    }
} // hasha
//
// Created by mythi on 22/07/22.
//

#include "LiteralExpression.h"

namespace hasha {
    nlohmann::json LiteralExpression::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "LiteralExpression";
        json["literal"] = m_literal;

        return json;
    }

    std::string LiteralExpression::to_string() const {

        return "LiteralExpression " + m_literal;
    }

    LiteralExpression::LiteralExpression(std::string literal) :
            m_literal(std::move(literal)) {}

    LiteralExpression::LiteralExpressionPtr LiteralExpression::create(std::string literal) {

        return std::shared_ptr<LiteralExpression>(new LiteralExpression(std::move(literal)));
    }

} // hasha
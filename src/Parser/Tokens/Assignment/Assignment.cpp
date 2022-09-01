//
// Created by mythi on 01/09/22.
//

#include "Assignment.h"

namespace hasha {
    nlohmann::json Assignment::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Assignment";
        json["expression"] = expression->to_json();
        return json;
    }

    Assignment::Assignment(Expression::Ptr expression) : expression(std::move(expression)) {

    }

    Assignment::Ptr Assignment::create(Expression::Ptr expression) {

        return std::make_unique<Assignment>(std::move(expression));
    }
} // hasha
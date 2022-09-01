//
// Created by mythi on 28/07/22.
//

#include "ArrayAssignment.h"

#include <memory>

namespace hasha {


    nlohmann::json ArrayAssignment::to_json() const {

        auto json = nlohmann::json();


        json["token_type"] = "ArrayAssignment";
        json["expressions"] = expression_list_to_json(m_expressions.get());

        return json;
    }

    ArrayAssignment::ArrayAssignment(ExpressionListPtr expressions) :
            Assignment(nullptr),
            m_expressions(std::move(expressions)) {}

    ArrayAssignment::Ptr ArrayAssignment::create(
            ExpressionListPtr expressions
    ) {

        return std::make_unique<ArrayAssignment>(
                std::move(expressions)
        );
    }

    const ExpressionList *ArrayAssignment::get_expressions() const {

        return m_expressions.get();
    }
} // hasha
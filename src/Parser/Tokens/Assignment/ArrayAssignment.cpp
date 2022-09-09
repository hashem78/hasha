//
// Created by mythi on 28/07/22.
//

#include "ArrayAssignment.h"

#include <memory>

namespace hasha {


    nlohmann::json ArrayAssignment::to_json() const {

        auto json = nlohmann::json();


        json["token_type"] = "ArrayAssignment";
        json["expressions"] = expression_list_to_json(m_expressions);
        json["span"] = m_span.to_json();

        return json;
    }

    ArrayAssignment::ArrayAssignment(
            ExpressionList expressions,
            const Span &span
    ) :
            Assignment(nullptr, span),
            m_expressions(std::move(expressions)) {}

    ArrayAssignment::Ptr ArrayAssignment::create(
            ExpressionList expressions,
            const Span &span
    ) {

        return std::make_unique<ArrayAssignment>(
                std::move(expressions),
                span
        );
    }

    const ExpressionList& ArrayAssignment::get_expressions() const {

        return m_expressions;
    }
} // hasha
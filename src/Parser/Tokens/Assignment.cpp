//
// Created by mythi on 01/09/22.
//

#include "Assignment.h"

namespace hasha {
    nlohmann::json Assignment::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Assignment";
        json["expression"] = expression->to_json();
        json["span"] = m_span.to_json();
        return json;
    }

    Assignment::Assignment(
            Expression::Ptr expression,
            const Span &span,
            int scope_id

    ) :
            expression(std::move(expression)),
            Token(span, scope_id) {
    }

    Assignment::Ptr Assignment::create(
            Expression::Ptr expression,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<Assignment>(std::move(expression), span, scope_id);
    }
} // hasha
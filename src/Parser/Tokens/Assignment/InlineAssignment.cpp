//
// Created by mythi on 17/09/22.
//

#include "InlineAssignment.h"

namespace hasha {
    InlineAssignment::InlineAssignment(
            Identifier::Ptr assignee,
            Expression::Ptr expression,
            const Span &span
    ) :
            assignee(std::move(assignee)),
            Assignment(std::move(expression), span) {

    }

    InlineAssignment::Ptr InlineAssignment::create(
            Identifier::Ptr assignee,
            Expression::Ptr expression,
            const Span &span
    ) {

        return std::make_unique<InlineAssignment>(std::move(assignee), std::move(expression), span);
    }

    nlohmann::json InlineAssignment::to_json() const {

        auto json = Assignment::to_json();
        json["token_type"] = "InlineAssignment";
        json["asignee"] = assignee->to_json();
        return json;
    }
} // hasha
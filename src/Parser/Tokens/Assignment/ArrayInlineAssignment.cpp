//
// Created by mythi on 17/09/22.
//

#include "ArrayInlineAssignment.h"

namespace hasha {
    ArrayInlineAssignment::ArrayInlineAssignment(
            Identifier::Ptr assignee,
            ExpressionList expressions,
            const Span &span
    ) :
            assignee(std::move(assignee)),
            m_expressions(std::move(expressions)),
            Assignment(nullptr, span) {

    }

    ArrayInlineAssignment::Ptr ArrayInlineAssignment::create(
            Identifier::Ptr assignee,
            ExpressionList expressions,
            const Span &span
    ) {

        return std::make_unique<ArrayInlineAssignment>(std::move(assignee), std::move(expressions), span);
    }

    nlohmann::json ArrayInlineAssignment::to_json() const {

        auto json = Assignment::to_json();
        json["token_type"] = "ArrayInlineAssignment";
        json["asignee"] = assignee->to_json();
        json["expressions"] = expression_list_to_json(m_expressions);
        return json;
    }
} // hasha
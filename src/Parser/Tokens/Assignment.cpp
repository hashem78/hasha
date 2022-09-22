//
// Created by mythi on 01/09/22.
//

#include "Assignment.h"

namespace hasha {
    nlohmann::json Assignment::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Assignment";
        json["assignee"] = m_assignee->to_json();
        json["expression"] = m_expression->to_json();
        json["span"] = m_span.to_json();
        return json;
    }

    Assignment::Assignment(
            Identifier::Ptr assignee,
            Expression::Ptr expression,
            const Span &span,
            int scope_id

    ) :
            m_assignee(std::move(assignee)),
            m_expression(std::move(expression)),
            Token(span, scope_id) {
    }

    Assignment::Ptr Assignment::create(
            Identifier::Ptr assignee,
            Expression::Ptr expression,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<Assignment>(
                std::move(assignee),
                std::move(expression),
                span, scope_id
        );
    }

    const Expression &Assignment::expression() const {

        return *m_expression;
    }

    const Identifier &Assignment::assignee() const {

        return *m_assignee;
    }
} // hasha
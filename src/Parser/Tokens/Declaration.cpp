//
// Created by mythi on 21/07/22.
//

#include "Declaration.h"

namespace hasha {
    const Type& Declaration::type() const {

        return *m_type;
    }

    const Identifier& Declaration::name() const {

        return m_name;
    }


    nlohmann::json Declaration::to_json() const {

        auto json = nlohmann::json();

        json["name"] = m_name.to_json();
        json["type"] = m_type->to_json();

        json["token_type"] = "Declaration";

        if (m_assignment_expression != nullptr) {

            json["assignment_expression"] = m_assignment_expression->to_json();

        }
        json["span"] = m_span.to_json();

        return json;
    }

    Declaration::Declaration(
            Type::Ptr type,
            Identifier name,
            const Span &span,
            int scope_id,
            Expression::Ptr assignment_expression
    ) :
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_assignment_expression(std::move(assignment_expression)),
            Token(span, scope_id) {}

    Declaration::Ptr
    Declaration::create(
            Type::Ptr type,
            Identifier name,
            const Span &span,
            int scope_id,
            Expression::Ptr assignment_expression
    ) {

        return std::make_unique<Declaration>(
                std::move(type),
                std::move(name),
                span,
                scope_id,
                std::move(assignment_expression)
        );
    }

    const Expression &Declaration::assignment_expression() const {

        return *m_assignment_expression;
    }

} // hasha
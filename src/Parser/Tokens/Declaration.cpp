//
// Created by mythi on 21/07/22.
//

#include "Declaration.h"

namespace hasha {
    const Type *Declaration::get_type() const {

        return m_type.get();
    }

    Identifier Declaration::get_name() const {

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

    ErrorOr<void> Declaration::interpret(const ScopeTree &scope_tree) {

        auto scope = scope_tree.get_by_id(m_scope_id);
        auto res = m_assignment_expression->evaluate(*scope);
        scope->symbol_table.set_vaiable_value(m_name.get(), {res});
        fmt::print("Assigned {} with {}\n", m_name.get(), res);

        return {};
    }

} // hasha
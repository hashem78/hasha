//
// Created by mythi on 01/10/22.
//

#include "Declaration.h"

namespace hasha {

    Declaration::Declaration(
            std::variant<Box<NormalType>, Box<GenericType>> type,
            Box<Identifier> name,
            Box<Expression> assignment_expression,
            Span span,
            int scope_id
    ) noexcept:
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_assignment_expression(std::move(assignment_expression)),
            TokenBase(span, scope_id, "Declaration"sv) {}

    const std::variant<Box<NormalType>, Box<GenericType>> &Declaration::type() const noexcept {

        return m_type;
    }

    const Box<Identifier> &Declaration::name() const noexcept {

        return m_name;
    }

    const Box<Expression> &Declaration::assignment_expression() const noexcept {

        return m_assignment_expression;
    }
} // hasha
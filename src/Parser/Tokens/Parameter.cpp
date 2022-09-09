//
// Created by mythi on 25/07/22.
//

#include "Parameter.h"

namespace hasha {
    Parameter::Parameter(
            Type::Ptr type,
            Identifier name,
            const Span &span
    ) noexcept:
            m_type(std::move(type)),
            m_name(std::move(name)),
            Token(span) {

    }

    Parameter::Ptr Parameter::create(
            Type::Ptr type,
            Identifier name,
            const Span &span
    ) {

        return std::make_unique<Parameter>(
                std::move(type),
                std::move(name),
                span
        );
    }

    nlohmann::json Parameter::to_json() const {

        return {
                {"token_type", "Parameter"},
                {"type",       m_type->to_json()},
                {"name",       m_name.to_json()},
                {"span",      m_span.to_json()}
        };
    }

    const Identifier &Parameter::get_name() const noexcept {

        return m_name;
    }

    const Type *Parameter::get_type() const noexcept {

        return m_type.get();
    }
} // hasha
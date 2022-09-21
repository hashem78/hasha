//
// Created by mythi on 25/07/22.
//

#include "Parameter.h"

namespace hasha {
    Parameter::Parameter(
            Type::Ptr type,
            Identifier name,
            const Span &span,
            int scope_id
    ) noexcept:
            m_type(std::move(type)),
            m_name(std::move(name)),
            Token(span, scope_id) {

    }

    Parameter::Ptr Parameter::create(
            Type::Ptr type,
            Identifier name,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<Parameter>(
                std::move(type),
                std::move(name),
                span,
                scope_id
        );
    }

    nlohmann::json Parameter::to_json() const {

        return {
                {"token_type", "Parameter"},
                {"type",       m_type->to_json()},
                {"name",       m_name.to_json()},
                {"span",       m_span.to_json()}
        };
    }

    const Identifier &Parameter::get_name() const noexcept {

        return m_name;
    }

    const Type& Parameter::type() const noexcept {

        return *m_type;
    }

    nlohmann::json parameter_list_to_json(const ParameterList &parameter_list) {

        auto json = nlohmann::json::array();

        for (const auto &param: parameter_list) {
            json.push_back(param->to_json());
        }

        return json;
    }
} // hasha
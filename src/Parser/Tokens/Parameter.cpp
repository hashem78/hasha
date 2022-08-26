//
// Created by mythi on 25/07/22.
//

#include "Parameter.h"

#include <memory>

namespace hasha {
    Parameter::Parameter(Identifier type, Identifier name) noexcept:
            m_type(std::move(type)),
            m_name(std::move(name)) {

    }

    Parameter::Ptr Parameter::create(Identifier type, Identifier name) {

        return std::make_unique<Parameter>(std::move(name), std::move(type));
    }

    nlohmann::json Parameter::to_json() const {

        return {
                {"token_type", "Parameter"},
                {"type",       m_type.to_json()},
                {"name",       m_name.to_json()}
        };
    }

    const Identifier &Parameter::get_name() const noexcept {

        return m_name;
    }

    const Identifier &Parameter::get_type() const noexcept {

        return m_type;
    }
} // hasha
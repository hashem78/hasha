//
// Created by mythi on 25/07/22.
//

#include "Parameter.h"

namespace hasha {
    Parameter::Parameter(std::string name, std::string type) noexcept: m_name(std::move(name)),
                                                                       m_type(std::move(type)) {

    }

    Parameter::Ptr Parameter::create(std::string name, std::string type) {

        return std::unique_ptr<Parameter>(new Parameter(std::move(name), std::move(type)));
    }

    nlohmann::json Parameter::to_json() const {

        return {
                {"token_type", "Parameter"},
                {"name",       m_name},
                {"type",       m_type}
        };
    }

    std::string Parameter::to_string() const {

        return fmt::format("Parameter {} {}", m_name, m_type);
    }

    const std::string &Parameter::get_name() const noexcept {

        return m_name;
    }

    const std::string &Parameter::get_type() const noexcept {

        return m_type;
    }
} // hasha
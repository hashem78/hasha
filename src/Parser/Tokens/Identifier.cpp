//
// Created by mythi on 24/07/22.
//

#include "Identifier.h"

namespace hasha {

    Identifier::Identifier(std::string name) noexcept: m_name(std::move(name)) {

    }

    Identifier::Ptr Identifier::create(std::string name) {

        return std::unique_ptr<Identifier>(new Identifier(std::move(name)));
    }

    nlohmann::json Identifier::to_json() const {

        return {
                {"token_type", "Identifier"},
                {"name",       m_name}
        };
    }

    std::string Identifier::to_string() const {

        return fmt::format("Identitifer {}", m_name);
    }

    const std::string &Identifier::get_name() const noexcept {

        return m_name;
    }

    void Identifier::set_name(const std::string &name) noexcept {

        Identifier::m_name = name;
    }

} // hasha
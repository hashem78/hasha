//
// Created by mythi on 24/07/22.
//

#include "Identifier.h"

#include <memory>

namespace hasha {

    Identifier::Identifier(std::string identifier) noexcept: m_identifier(std::move(identifier)) {

    }

    Identifier::Ptr Identifier::create(std::string identifier) {

        return std::make_unique<Identifier>(std::move(identifier));
    }

    nlohmann::json Identifier::to_json() const {

        return {
                {"token_type", "Identifier"},
                {"identifier", m_identifier}
        };
    }

    const std::string &Identifier::get() const noexcept {

        return m_identifier;
    }

    void Identifier::set(const std::string &identifier) noexcept {

        Identifier::m_identifier = identifier;
    }

} // hasha
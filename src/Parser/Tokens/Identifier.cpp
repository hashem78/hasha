//
// Created by mythi on 24/07/22.
//

#include "Identifier.h"

namespace hasha {

    Identifier::Identifier(
            std::string identifier,
            const Span &span
    ) noexcept:
            m_identifier(std::move(identifier)),
            Token(span) {

    }

    Identifier::Ptr Identifier::create(
            std::string identifier,
            const Span &span
    ) {

        return std::make_unique<Identifier>(std::move(identifier), span);
    }

    nlohmann::json Identifier::to_json() const {

        return {
                {"token_type", "Identifier"},
                {"identifier", m_identifier},
                {"span",       m_span.to_json()}
        };
    }

    const std::string &Identifier::get() const noexcept {

        return m_identifier;
    }

    void Identifier::set(const std::string &identifier) noexcept {

        Identifier::m_identifier = identifier;
    }

} // hasha
//
// Created by mythi on 24/07/22.
//

#include "Identifier.h"

namespace hasha {

    Identifier::Identifier(
            std::string identifier,
            const Span &span,
            int scope_id
    ) noexcept:
            m_identifier(std::move(identifier)),
            Token(span,scope_id) {

    }

    Identifier::Ptr Identifier::create(
            std::string identifier,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<Identifier>(std::move(identifier), span, scope_id);
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
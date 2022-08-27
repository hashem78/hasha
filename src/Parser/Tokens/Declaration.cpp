//
// Created by mythi on 21/07/22.
//

#include "Declaration.h"

#include <memory>

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

        if (m_assignment != nullptr) {

            json["tokens"] = m_assignment->to_json();

        }

        return json;
    }

    Declaration::Declaration(
            Type::Ptr type,
            Identifier name,
            Assignment::Ptr assignment
    ) :
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_assignment(std::move(assignment)) {}

    Declaration::Ptr
    Declaration::create(
            Type::Ptr type,
            Identifier name,
            Assignment::Ptr tokens
    ) {

        return std::make_unique<Declaration>(
                std::move(type),
                std::move(name),
                std::move(tokens)
        );
    }

    TokenListPtr Declaration::get_tokens() const {

        return m_assignment->get_tokens();
    }


} // hasha
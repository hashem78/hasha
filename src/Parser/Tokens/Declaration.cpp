//
// Created by mythi on 21/07/22.
//

#include "Declaration.h"
#include "Type/ArrayType.h"

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

            json["assignment"] = m_assignment->to_json();

        }
        json["span"] = m_span.to_json();

        return json;
    }

    Declaration::Declaration(
            Type::Ptr type,
            Identifier name,
            const Span &span,
            Assignment::Ptr assignment
    ) :
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_assignment(std::move(assignment)),
            Token(span) {}

    Declaration::Ptr
    Declaration::create(
            Type::Ptr type,
            Identifier name,
            const Span &span,
            Assignment::Ptr tokens
    ) {

        return std::make_unique<Declaration>(
                std::move(type),
                std::move(name),
                span,
                std::move(tokens)
        );
    }

    ErrorOr<void> Declaration::interpret() {


        return {};
    }

} // hasha
//
// Created by mythi on 27/08/22.
//

#include "Type.h"


namespace hasha {

    Type::Type(
            std::string type,
            const Span &span,
            int scope_id
    ) :
            type(std::move(type)),
            Token(span, scope_id) {

    }

    Type::Ptr Type::create(
            std::string type,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<Type>(std::move(type), span, scope_id);
    }

    const std::string &Type::get_type() const {

        return type;
    }

    nlohmann::json Type::to_json() const {

        auto json = nlohmann::json();
        json["type"] = type;
        json["token_type"] = "Type";
        json["span"] = m_span.to_json();
        return json;
    }

    bool Type::operator==(const Type &other) const {

        return type == other.type;
    }

    nlohmann::json type_list_to_json(const TypeList &type_list) {

        auto json = nlohmann::json::array();
        for (const auto &type: type_list) {
            json.push_back(type->to_json());
        }
        return json;
    }
} // hasha
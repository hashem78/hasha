//
// Created by mythi on 27/08/22.
//

#include "Type.h"



namespace hasha {

    Type::Type(std::string type, const Span &span) : type(std::move(type)), Token(span) {

    }

    Type::Ptr Type::create(std::string type, const Span &span) {

        return std::make_unique<Type>(std::move(type), span);
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

} // hasha
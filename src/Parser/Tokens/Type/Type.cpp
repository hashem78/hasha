//
// Created by mythi on 27/08/22.
//

#include "Type.h"

#include <utility>

namespace hasha {

    Type::Type(Identifier name, const Span &span) : name(std::move(name)), Token(span) {

    }

    Type::Ptr Type::create(Identifier name, const Span &span) {

        return std::make_unique<Type>(std::move(name), span);
    }

    const Identifier &Type::get_name() const {

        return name;
    }

    nlohmann::json Type::to_json() const {

        auto json = nlohmann::json();
        json["name"] = name.to_json();
        json["token_type"] = "Type";
        json["span"] =m_span.to_json();
        return json;
    }

} // hasha
//
// Created by mythi on 27/08/22.
//

#include "Type.h"

#include <utility>

namespace hasha {

    Type::Type(Identifier name) : name(std::move(name)) {

    }

    Type::Ptr Type::create(Identifier name) {

        return std::make_unique<Type>(std::move(name));
    }
    const Identifier &Type::get_name() const {

        return name;
    }

    nlohmann::json Type::to_json() const {

        auto json = nlohmann::json();
        json["name"] = name.to_json();
        json["token_type"] = "Type";
        return json;
    }

} // hasha
//
// Created by mythi on 27/08/22.
//

#include "ArrayType.h"

namespace hasha {
    nlohmann::json ArrayType::to_json() const {

        auto json = Type::to_json();
        json["token_type"] = "ArrayType";
        return json;
    }

    ArrayType::Ptr ArrayType::create(std::string type, const Span &span) {

        return std::make_unique<ArrayType>(std::move(type), span);
    }
} // hasha
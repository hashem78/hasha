//
// Created by mythi on 26/08/22.
//
#include "BooleanLiteral.h"

namespace hasha {

    std::unique_ptr<BooleanLiteral> hasha::BooleanLiteral::create(std::string literal) {

        return std::make_unique<BooleanLiteral>(std::move(literal));
    }

    nlohmann::json hasha::BooleanLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "BooleanLiteral"},
                {"literal",    m_literal}
        };
    }
}
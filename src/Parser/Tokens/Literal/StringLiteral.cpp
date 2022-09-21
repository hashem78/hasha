//
// Created by mythi on 26/08/22.
//
#include "StringLiteral.h"
#include "Type/DefaultTypes.h"

namespace hasha {

    StringLiteral::Ptr StringLiteral::create(std::string literal, const Span &span, int scope_id) {

        return std::make_unique<StringLiteral>(DefStringType, std::move(literal), span, scope_id);
    }

    nlohmann::json hasha::StringLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "StringLiteral"},
                {"literal",    m_literal},
                {"span",       m_span.to_json()}
        };
    }
}

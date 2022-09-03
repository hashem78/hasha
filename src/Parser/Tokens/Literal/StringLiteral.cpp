//
// Created by mythi on 26/08/22.
//
#include "StringLiteral.h"

namespace hasha {

    StringLiteral::Ptr StringLiteral::create(std::string literal, const Span &span) {

        return std::make_unique<StringLiteral>(std::move(literal), span);
    }

    nlohmann::json hasha::StringLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "StringLiteral"},
                {"literal",    m_literal},
                {"span",      m_span.to_json()}
        };
    }
}

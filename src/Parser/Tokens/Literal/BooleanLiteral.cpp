//
// Created by mythi on 26/08/22.
//
#include "BooleanLiteral.h"

namespace hasha {

    BooleanLiteral::Ptr BooleanLiteral::create(std::string literal, const Span &span) {

        return std::make_unique<BooleanLiteral>(std::move(literal), span);
    }

    nlohmann::json BooleanLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "BooleanLiteral"},
                {"literal",    m_literal},
                {"span",      m_span.to_json()}
        };
    }
}
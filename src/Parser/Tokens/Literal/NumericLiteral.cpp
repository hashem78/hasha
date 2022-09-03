//
// Created by mythi on 26/08/22.
//
#include "NumericLiteral.h"

namespace hasha {
    NumericLiteral::Ptr NumericLiteral::create(std::string literal, const Span &span) {

        return std::make_unique<NumericLiteral>(std::move(literal), span);
    }

    nlohmann::json NumericLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "NumericLiteral"},
                {"literal",    m_literal},
                {"span",      m_span.to_json()}
        };
    }


}
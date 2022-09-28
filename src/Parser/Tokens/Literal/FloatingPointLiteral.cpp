//
// Created by mythi on 26/08/22.
//
#include "FloatingPointLiteral.h"
#include "Type/DefaultParserTypes.h"

namespace hasha {
    FloatingPointLiteral::Ptr FloatingPointLiteral::create(std::string literal, const Span &span, int scope_id) {

        return std::make_unique<FloatingPointLiteral>(DefFloatingPointType, std::move(literal), span, scope_id);
    }

    nlohmann::json FloatingPointLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "FloatingPointLiteral"},
                {"literal",    m_literal},
                {"span",      m_span.to_json()}
        };
    }


}
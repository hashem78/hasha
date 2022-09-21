//
// Created by mythi on 26/08/22.
//
#include "BooleanLiteral.h"
#include "Type/DefaultTypes.h"

namespace hasha {

    BooleanLiteral::Ptr BooleanLiteral::create(
            std::string literal,
            const Span& span,
            int scope_id
    ) {

        return std::make_unique<BooleanLiteral>(DefBooleanType,std::move(literal), span, scope_id);
    }

    nlohmann::json BooleanLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "BooleanLiteral"},
                {"literal",    m_literal},
                {"span",       m_span.to_json()}
        };
    }
}
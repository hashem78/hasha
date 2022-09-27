//
// Created by mythi on 26/08/22.
//
#include "IntegerLiteral.h"
#include "Type/DefaultTypes.h"

namespace hasha {
    IntegerLiteral::Ptr IntegerLiteral::create(std::string literal, const Span &span, int scope_id) {

        return std::make_unique<IntegerLiteral>(DefIntegerType, std::move(literal), span, scope_id);
    }

    nlohmann::json IntegerLiteral::to_json() const {

        return nlohmann::json{
                {"token_type", "NumericLiteral"},
                {"literal",    m_literal},
                {"span",      m_span.to_json()}
        };
    }


}
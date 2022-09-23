//
// Created by mythi on 26/08/22.
//
#include "BinaryOperator.h"

namespace hasha {

    BinaryOperator::BinaryOperator(std::string op, const Span &span, int scope_id) noexcept:
            m_op(std::move(op)),
            Token(span,scope_id) {

    }

    const std::string &BinaryOperator::operation() const noexcept {

        return m_op;
    }

    BinaryOperator::Ptr BinaryOperator::create(std::string op, const Span &span, int scope_id) {

        return std::make_unique<BinaryOperator>(std::move(op), span, scope_id);
    }

    nlohmann::json BinaryOperator::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "BinaryOperator";
        json["operator"] = m_op;
        json["span"] =m_span.to_json();
        return json;
    }
}

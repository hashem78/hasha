//
// Created by mythi on 26/08/22.
//
#include "UnaryOperator.h"

namespace hasha {

    UnaryOperator::UnaryOperator(std::string op, const Span &span, int scope_id) noexcept:
            m_op(std::move(op)),
            Token(span,scope_id) {

    }

    const std::string &UnaryOperator::operation() const noexcept {

        return m_op;
    }

    UnaryOperator::Ptr UnaryOperator::create(std::string op, const Span &span, int scope_id) {

        return std::make_unique<UnaryOperator>(std::move(op), span, scope_id);
    }

    nlohmann::json UnaryOperator::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "UnaryOperator";
        json["operator"] = m_op;
        json["span"] =m_span.to_json();
        return json;
    }
}

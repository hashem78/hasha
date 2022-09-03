//
// Created by mythi on 26/08/22.
//
#include "Operator.h"

namespace hasha {

    Operator::Operator(std::string op, const Span &span) noexcept:
            m_op(std::move(op)),
            Token(span) {

    }

    const std::string &Operator::get_op() const noexcept {

        return m_op;
    }

    Operator::Ptr Operator::create(std::string op, const Span &span) {

        return std::make_unique<Operator>(std::move(op), span);
    }

    nlohmann::json Operator::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Operator";
        json["operator"] = m_op;
        json["span"] =m_span.to_json();
        return json;
    }
}

//
// Created by mythi on 12/08/22.
//

#include "FunctionCall.h"

#include <memory>
#include <utility>

namespace hasha {
    std::string FunctionCall::get_callee() const noexcept {

        return m_callee;
    }

    const ExpressionList *FunctionCall::get_arguments() const noexcept {

        return m_arguments.get();
    }

    FunctionCall::FunctionCall(
            std::string callee,
            ExpressionListPtr tokens,
            const Span &span) :
            m_callee(std::move(callee)),
            m_arguments(std::move(tokens)),
            Token(span) {

    }

    int FunctionCall::get_number_of_args() const noexcept {

        return static_cast<int>(m_arguments->size());
    }

    FunctionCall::Ptr FunctionCall::create(
            std::string callee,
            ExpressionListPtr tokens,
            const Span &span
    ) {

        return std::make_unique<FunctionCall>(
                std::move(callee),
                std::move(tokens),
                span
        );
    }

    nlohmann::json FunctionCall::to_json() const {

        auto json = nlohmann::json();

        json["token_type"] = "FunctionCall";
        json["callee"] = m_callee;
        json["arguments"] = expression_list_to_json(m_arguments.get());
        json["span"] = m_span.to_json();
        return json;
    }

} // hasha
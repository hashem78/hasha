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

    TokenListPtr FunctionCall::get_arguments() const noexcept {

        return m_arguments;
    }

    FunctionCall::FunctionCall(std::string callee, TokenListPtr tokens) :
            m_callee(std::move(callee)),
            m_arguments(std::move(tokens)) {

    }

    int FunctionCall::get_number_of_args() const noexcept {

        return static_cast<int>(m_arguments->size());
    }

    FunctionCall::Ptr FunctionCall::create(std::string callee, TokenListPtr tokens) {

        return std::make_unique<FunctionCall>(std::move(callee), std::move(tokens));
    }

    nlohmann::json FunctionCall::to_json() const {

        auto json = nlohmann::json();

        json["token_type"] = "FunctionCall";
        json["callee"] = m_callee;
        json["arguments"] = token_list_to_json(m_arguments.get());
        return json;
    }

} // hasha
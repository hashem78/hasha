//
// Created by mythi on 30/07/22.
//

#include "FunctionCall.h"

namespace hasha {
    FunctionCall::FunctionCall(Identifier::Ptr callee, TokenListPtr args) : m_callee(std::move(callee)),
                                                                            m_args(std::move(args)) {}

    FunctionCall::Ptr FunctionCall::create(Identifier::Ptr callee, TokenListPtr args) {

        return std::unique_ptr<FunctionCall>(new FunctionCall(std::move(callee), std::move(args)));
    }

    const Identifier::Ptr &FunctionCall::get_callee() const {

        return m_callee;
    }

    const TokenListPtr &FunctionCall::get_args() const {

        return m_args;
    }

    nlohmann::json FunctionCall::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "FunctionCall";
        json["callee"] = m_callee->to_json();
        json["args"] = nlohmann::json::array();
        for (const auto &arg: *m_args) {
            json["args"].push_back(arg->to_json());
        }
        return json;
    }

    std::string FunctionCall::to_string() const {

        auto str = fmt::format("FunctionCall {}\n", m_callee->to_string());
        for (const auto &arg: *m_args) {
            str += fmt::format(" - {}\n", arg->to_string());
        }

        return str;
    }
} // hasha
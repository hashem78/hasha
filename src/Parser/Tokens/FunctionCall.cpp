//
// Created by mythi on 11/08/22.
//

#include "FunctionCall.h"

#include <utility>

namespace hasha {
    nlohmann::json FunctionCall::to_json() const {

        return {
                {"token_type", "FunctionCall"},
                {"callee",     m_callee},
                {"arg_count",  m_arg_count}
        };
    }

    std::string FunctionCall::to_string() const {

        return fmt::format("{} {}-{}", "FunctionCall", m_callee, m_arg_count);
    }

    const std::string &FunctionCall::get_callee() const {

        return m_callee;
    }

    int FunctionCall::get_arg_count() const {

        return m_arg_count;
    }

    FunctionCall::FunctionCall(std::string callee, int arg_count) : m_callee(std::move(callee)),
                                                                    m_arg_count(arg_count) {

    }

    FunctionCall::Ptr FunctionCall::create(std::string callee, int arg_count) {

        return std::unique_ptr<FunctionCall>(new FunctionCall(std::move(callee), arg_count));
    }
} // hasha
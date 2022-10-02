//
// Created by mythi on 01/10/22.
//

#include "FunctionCall.h"

namespace hasha {

    FunctionCall::FunctionCall(
            std::string callee,
            std::vector<Box<Expression>> tokens,
            const Span &span,
            int scope_id
    ) :
            m_callee(std::move(callee)),
            m_arguments(std::move(tokens)),
            TokenBase(span, scope_id, "FunctionCall"sv) {

    }

    const std::string &FunctionCall::callee() const noexcept {

        return m_callee;
    }

    const std::vector<Box<Expression>> &FunctionCall::arguments() const noexcept {

        return m_arguments;
    }

    int FunctionCall::number_of_args() const noexcept {

        return static_cast<int>(m_arguments.size());
    }
} // hasha
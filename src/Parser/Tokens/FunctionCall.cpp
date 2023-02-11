//
// Created by mythi on 01/10/22.
//

#include "FunctionCall.h"

namespace hasha {

  FunctionCall::FunctionCall(
    std::string callee,
    std::vector<Box<Expression>> tokens,
    Span span,
    uuid scope_id
  )
      : m_callee(std::move(callee)),
        m_arguments(std::move(tokens)),
        CONSTRUCT_DETAILS(FunctionCall) {
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
}// namespace hasha
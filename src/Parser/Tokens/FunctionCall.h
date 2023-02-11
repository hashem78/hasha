//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"

namespace hasha {

  class [[nodiscard]] FunctionCall final {
    std::string m_callee;
    std::vector<Box<Expression>> m_arguments;

    DEFINE_DETAILS()
   public:
    FunctionCall(
      std::string callee,
      std::vector<Box<Expression>> tokens,
      Span span,
      uuid scope_id
    );


    [[nodiscard]] int number_of_args() const noexcept;

    [[nodiscard]] const std::string &callee() const noexcept;

    [[nodiscard]] const std::vector<Box<Expression>> &arguments() const noexcept;
  };

  using BoxedFunctionCall = Box<FunctionCall>;
}// namespace hasha

#endif//HASHA_FUNCTIONCALL_H

//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_TOKEN_H
#define HASHA_TOKEN_H

#include "Box.h"
#include "TokenForwards.h"
#include <optional>
#include <variant>
#include <vector>

#define EXTRACT(EXTRACTABLE) \
  EXTRACTABLE.value().get()

namespace hasha {
  using InternalToken = std::variant<
    Box<Identifier>,
    std::variant<Box<NormalType>, Box<GenericType>>,
    Box<Expression>,
    Box<Declaration>,
    Box<Literal>,
    Box<Operator>,
    Box<FunctionCall>,
    Box<Block>,
    Box<Function>,
    Box<Assignment>,
    Box<Parameter>,
    Box<IfStatement>,
    Box<ElifStatement>,
    Box<ElseStatement>,
    Box<ReturnToken>>;
  class [[nodiscard]] Token final : public InternalToken {
   public:
    using InternalToken::variant;

    template<typename T>
    const Box<T> &get() const {
      return std::get<Box<T>>(*this);
    }

    template<typename T>
    std::optional<std::reference_wrapper<const Box<T>>> as() const noexcept {
      if (std::holds_alternative<Box<T>>(*this)) {
        return std::cref(std::get<Box<T>>(*this));
      }
      return {};
    }

    template<typename T>
    bool is() const noexcept {
      return std::holds_alternative<Box<T>>(*this);
    }
  };
}// namespace hasha

#endif//HASHA_TOKEN_H

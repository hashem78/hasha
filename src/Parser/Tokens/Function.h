//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_FUNCTION_H
#define HASHA_FUNCTION_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"
#include <variant>

namespace hasha {


  class Function : public TokenBase {

    Box<Identifier> m_name;
    std::vector<Box<Parameter>> m_parameters;
    std::variant<Box<NormalType>, Box<GenericType>> m_return_type;
    Box<Block> m_block;

   public:
    Function(
      Box<Identifier> name,
      std::vector<Box<Parameter>> parameters,
      std::variant<Box<NormalType>, Box<GenericType>> return_type,
      Box<Block> block,
      Span span,
      int scope_id
    ) noexcept;

    [[nodiscard]] const Box<Identifier> &name() const noexcept;

    [[nodiscard]] const std::variant<Box<NormalType>, Box<GenericType>> &return_type() const noexcept;

    [[nodiscard]] const std::vector<Box<Parameter>> &parameters() const noexcept;

    [[nodiscard]] int number_of_parameters() const noexcept;

    [[nodiscard]] const Box<Block> &block() const noexcept;
  };

  using BoxedFunction = Box<Function>;
}// namespace hasha

#endif//HASHA_FUNCTION_H

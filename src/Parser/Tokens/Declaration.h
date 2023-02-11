//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Box.h"
#include "TokenBase.h"
#include "TokenForwards.h"
#include <variant>


namespace hasha {

  class [[nodiscard]] Declaration final {
   protected:
    std::variant<Box<NormalType>, Box<GenericType>> m_type;
    Box<Identifier> m_name;
    Box<Expression> m_assignment_expression;

    DEFINE_DETAILS()
   public:
    Declaration(
      std::variant<Box<NormalType>, Box<GenericType>> type,
      Box<Identifier> name,
      Box<Expression> assignment_expression,
      Span span,
      uuid scope_id
    ) noexcept;

    [[nodiscard]] const std::variant<Box<NormalType>, Box<GenericType>> &type() const noexcept;

    [[nodiscard]] const Box<Identifier> &name() const noexcept;

    [[nodiscard]] const Box<Expression> &assignment_expression() const noexcept;
  };

  using BoxedDeclaration = Box<Declaration>;
  using BoxedDeclarationList = std::vector<BoxedDeclaration>;
}// namespace hasha

#endif//HASHA_DECLARATION_H
//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_LITERAL_H
#define HASHA_LITERAL_H

#include "Box.h"
#include "LiteralType.h"
#include "TokenBase.h"

namespace hasha {

  class [[nodiscard]] Literal final {
   protected:
    LiteralType m_type;
    std::string m_literal;

    DEFINE_DETAILS()
   public:
    Literal(
      LiteralType type,
      std::string literal,
      Span span,
      uuid scope_id
    );

    [[nodiscard]] const std::string &literal() const noexcept;

    [[nodiscard]] LiteralType type() const;
  };

  using BoxedLiteral = Box<Literal>;
}// namespace hasha

#endif//HASHA_LITERAL_H

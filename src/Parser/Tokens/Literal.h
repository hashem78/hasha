//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_LITERAL_H
#define HASHA_LITERAL_H

#include "Box.h"
#include "LiteralType.h"
#include "TokenBase.h"

namespace hasha {

  class Literal : public TokenBase {
   protected:
    LiteralType m_type;
    std::string m_literal;

   public:
    Literal(
      LiteralType type,
      std::string literal,
      Span span,
      int scope_id
    );

    [[nodiscard]] const std::string &literal() const noexcept;

    [[nodiscard]] LiteralType type() const;
  };

  using BoxedLiteral = Box<Literal>;
}// namespace hasha

#endif//HASHA_LITERAL_H

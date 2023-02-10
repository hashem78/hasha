//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_IDENTIFIER_H
#define HASHA_IDENTIFIER_H

#include "Box.h"
#include "TokenBase.h"

namespace hasha {

  class Identifier : public TokenBase {

    std::string m_identifier;

   public:
    explicit Identifier(
      std::string identifier,
      const Span &span,
      int scope_id
    ) noexcept;

    [[nodiscard]] const std::string &identifier() const noexcept;
  };

  using BoxedIdentifier = Box<Identifier>;

}// namespace hasha

#endif//HASHA_IDENTIFIER_H

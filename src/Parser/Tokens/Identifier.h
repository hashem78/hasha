//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_IDENTIFIER_H
#define HASHA_IDENTIFIER_H

#include "Box.h"
#include "TokenBase.h"

namespace hasha {

  class [[nodiscard]] Identifier final {

    std::string m_identifier;

    DEFINE_DETAILS()
   public:
    explicit Identifier(
      std::string identifier,
      Span span,
      uuid scope_id
    ) noexcept;

    [[nodiscard]] const std::string &identifier() const noexcept;
  };

  using BoxedIdentifier = Box<Identifier>;

}// namespace hasha

#endif//HASHA_IDENTIFIER_H

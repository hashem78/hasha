//
// Created by mythi on 01/10/22.
//

#include "Identifier.h"

namespace hasha {
  Identifier::Identifier(
    std::string identifier,
    const Span &span,
    int scope_id
  ) noexcept
      : m_identifier(std::move(identifier)),
        TokenBase(span, scope_id, "Identifier"sv) {
  }

  const std::string &Identifier::identifier() const noexcept {

    return m_identifier;
  }

}// namespace hasha
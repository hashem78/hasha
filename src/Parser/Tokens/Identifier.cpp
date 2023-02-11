//
// Created by mythi on 01/10/22.
//

#include "Identifier.h"

namespace hasha {
  Identifier::Identifier(
    std::string identifier,
    Span span,
    uuid scope_id
  ) noexcept
      : m_identifier(std::move(identifier)),
        CONSTRUCT_DETAILS(Identifier) {
  }

  const std::string &Identifier::identifier() const noexcept {

    return m_identifier;
  }

}// namespace hasha
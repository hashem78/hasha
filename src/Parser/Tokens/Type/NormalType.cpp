//
// Created by mythi on 01/10/22.
//

#include "NormalType.h"

namespace hasha {
  NormalType::NormalType(
    std::string type,
    Span span,
    uuid scope_id
  )
      : m_type(std::move(type)),
        CONSTRUCT_DETAILS(NormalType) {
  }

  bool NormalType::operator==(const NormalType &other) const {

    return m_type == other.m_type;
  }

  const std::string &NormalType::type() const {

    return m_type;
  }
}// namespace hasha
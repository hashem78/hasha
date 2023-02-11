//
// Created by mythi on 02/10/22.
//

#include "Parameter.h"

namespace hasha {
  Parameter::Parameter(
    std::variant<Box<NormalType>, Box<GenericType>> type,
    Box<Identifier> name,
    Span span,
    uuid scope_id
  ) noexcept
      : m_type(std::move(type)),
        m_name(std::move(name)),
        CONSTRUCT_DETAILS(Parameter) {
  }

  const Box<Identifier> &Parameter::name() const noexcept {

    return m_name;
  }

  const std::variant<Box<NormalType>, Box<GenericType>> &Parameter::type() const noexcept {

    return m_type;
  }
}// namespace hasha
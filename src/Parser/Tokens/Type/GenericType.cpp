//
// Created by mythi on 01/10/22.
//

#include "GenericType.h"
#include "NormalType.h"
#include "Overload.h"
#include "TypeComparer.h"

namespace hasha {
  GenericType::GenericType(
    BoxedType type,
    BoxedTypeList generics_list,
    Span span,
    int scope_id
  )
      : m_type(std::move(type)),
        m_generics_list(std::move(generics_list)),
        TokenBase(span, scope_id, "GenericType"sv) {
  }

  const BoxedType &GenericType::type() const {

    return m_type;
  }

  const BoxedTypeList &GenericType::generics_list() const {

    return m_generics_list;
  }

  bool GenericType::operator==(const GenericType &other) const noexcept {

    if (!std::visit(TypeComparer{}, m_type, other.m_type)) {
      return false;
    }

    if (m_generics_list.size() != other.m_generics_list.size())
      return false;
    for (size_t i = 0; i < m_generics_list.size(); i++) {
      if (!std::visit(TypeComparer{}, m_generics_list[i], other.m_generics_list[i]))
        return false;
    }
    return true;
  }
}// namespace hasha
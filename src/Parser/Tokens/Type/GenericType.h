//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_GENERICTYPE_H
#define HASHA_GENERICTYPE_H

#include "TokenBase.h"
#include "Type.h"

namespace hasha {

  class [[nodiscard]] GenericType final {
    BoxedType m_type;
    BoxedTypeList m_generics_list;

    DEFINE_DETAILS()
   public:
    GenericType(
      BoxedType type,
      BoxedTypeList generics_list,
      Span span,
      uuid scope_id
    );

    [[nodiscard]] bool operator==(const GenericType &other) const noexcept;

    [[nodiscard]] const BoxedType &type() const;

    [[nodiscard]] const BoxedTypeList &generics_list() const;
  };
}// namespace hasha
#endif//HASHA_GENERICTYPE_H

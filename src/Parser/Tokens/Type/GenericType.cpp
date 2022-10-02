//
// Created by mythi on 01/10/22.
//

#include "GenericType.h"

namespace hasha {
    GenericType::GenericType(
            BoxedType type,
            BoxedTypeList generics_list,
            Span span,
            int scope_id
    ) :
            m_type(std::move(type)),
            m_generics_list(std::move(generics_list)),
            TokenBase(span, scope_id, "GenericType"sv) {

    }

    const BoxedType &GenericType::type() const {

        return m_type;
    }

    const BoxedTypeList &GenericType::generics_list() const {

        return m_generics_list;
    }
} // hasha
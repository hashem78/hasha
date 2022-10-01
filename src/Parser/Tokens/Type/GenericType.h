//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_GENERICTYPE_H
#define HASHA_GENERICTYPE_H

#include "TokenBase.h"
#include "Type.h"
namespace hasha {

    class GenericType : public TokenBase {
        BoxedType m_type;
        BoxedTypeList m_generics_list;

    public:
        using Ptr = std::unique_ptr<GenericType>;

        GenericType(
                BoxedType type,
                BoxedTypeList generics_list,
                Span span,
                int scope_id
        );

    };
} // hasha
#endif //HASHA_GENERICTYPE_H

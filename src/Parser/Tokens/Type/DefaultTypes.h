//
// Created by mythi on 20/09/22.
//

#ifndef HASHA_DEFAULTTYPES_H
#define HASHA_DEFAULTTYPES_H

#include "Type.h"

namespace hasha {
    static inline const Type DefIntegerType{"int", Span{}, 0};
    static inline const Type DefStringType{"string", Span{}, 0};
    static inline const Type DefBooleanType{"bool", Span{}, 0};
}

#endif //HASHA_DEFAULTTYPES_H

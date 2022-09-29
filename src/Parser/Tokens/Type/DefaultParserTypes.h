//
// Created by mythi on 20/09/22.
//

#ifndef HASHA_DEFAULTPARSERTYPES_H
#define HASHA_DEFAULTPARSERTYPES_H

#include "Type.h"

namespace hasha {
    static inline const Type DefIntegerType{"int", Span{}, 0};
    static inline const Type DefFloatingPointType{"float", Span{}, 0};
    static inline const Type DefStringType{"string", Span{}, 0};
    static inline const Type DefBooleanType{"bool", Span{}, 0};
    static inline const Type DefVoidType{"void", Span{}, 0};
}

#endif //HASHA_DEFAULTPARSERTYPES_H

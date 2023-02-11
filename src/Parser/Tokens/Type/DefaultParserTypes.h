

//
// Created by mythi on 20/09/22.
//

#ifndef HASHA_DEFAULTPARSERTYPES_H
#define HASHA_DEFAULTPARSERTYPES_H

#include "Box.h"
#include "NormalType.h"
#include "Span.h"

namespace hasha {
  static inline const auto DefIntegerType = make_box<NormalType>("int", Span{}, generate_uuid());
  static inline const auto DefFloatingPointType = make_box<NormalType>("float", Span{}, generate_uuid());
  static inline const auto DefStringType = make_box<NormalType>("string", Span{}, generate_uuid());
  static inline const auto DefBooleanType = make_box<NormalType>("bool", Span{}, generate_uuid());
  static inline const auto DefVoidType = make_box<NormalType>("void", Span{}, generate_uuid());
}// namespace hasha

#endif//HASHA_DEFAULTPARSERTYPES_H
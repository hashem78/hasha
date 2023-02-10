//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_TYPE_H
#define HASHA_TYPE_H

#include "Box.h"
#include "TokenForwards.h"
#include <variant>

namespace hasha {
  using BoxedNormalType = Box<NormalType>;
  using BoxedGenericType = Box<GenericType>;
  using BoxedType = std::variant<BoxedNormalType, BoxedGenericType>;
  using BoxedTypeList = std::vector<BoxedType>;
}// namespace hasha

#endif//HASHA_TYPE_H

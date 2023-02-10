//
// Created by mythi on 04/10/22.
//

#ifndef HASHA_TYPECOMPARER_H
#define HASHA_TYPECOMPARER_H


#include "Box.h"
#include "GenericType.h"
#include "NormalType.h"
#include "fmt/core.h"

namespace hasha {
  struct TypeComparer {
    bool operator()(const BoxedNormalType &a, const BoxedNormalType &b) const noexcept {

      return *a == *b;
    }

    bool operator()(const BoxedGenericType &a, const BoxedGenericType &b) const noexcept {

      return *a == *b;
    }

    bool operator()(auto, auto) const noexcept {

      return false;
    }
  };
}// namespace hasha

#endif//HASHA_TYPECOMPARER_H

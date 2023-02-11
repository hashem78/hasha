#pragma once

#include "Type/GenericType.h"
#include "Type/NormalType.h"
#include "fmt/core.h"
#include <string>
#include <variant>
namespace hasha {
  struct BoxedTypeToString {

    std::string operator()(const Box<NormalType> &type) {

      return type->type();
    }

    std::string operator()(const Box<GenericType> &generic_type) {

      return fmt::format(
        "<{}>",
        std::visit(BoxedTypeToString{}, generic_type->type())
      );
    }
  };
}// namespace hasha
//
// Created by mythi on 03/10/22.
//

#include "Variable.h"
#include "Overload.h"
#include "Type/Type.h"
#include "fmt/core.h"

#include <utility>

namespace hasha::lang {
  Variable::Variable(
    std::string name,
    BoxedType type,
    VariableValue value
  )
      : name(std::move(name)),
        type(std::move(type)),
        value(std::move(value)) {
  }

  void Variable::print() const {

    auto val = std::visit(
      Overload{
        [](const int &val) { return std::to_string(val); },
        [](const float &val) { return std::to_string(val); },
        [](const bool &val) { return std::to_string(val); },
        [](const std::string &val) { return val; }},
      value
    );
    fmt::print("Variable: {} {}", name, val);
  }
}// namespace hasha::lang
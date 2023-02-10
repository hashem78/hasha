//
// Created by mythi on 03/10/22.
//

#include "Variable.h"
#include "Overload.h"
#include "fmt/core.h"

#include <utility>

namespace hasha::lang {
  Variable::Variable(
    std::string name,
    VariableValue value
  )
      : name(std::move(name)),
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
    fmt::print("Variable: {} {}\n", name, val);
  }
}// namespace hasha::lang
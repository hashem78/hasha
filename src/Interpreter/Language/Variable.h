//
// Created by mythi on 03/10/22.
//

#ifndef HASHA_VARIABLE_H
#define HASHA_VARIABLE_H

#include "Type/Type.h"
#include <string>
#include <variant>

namespace hasha::lang {
  using VariableValue = std::variant<int, float, bool>;

  struct Variable {
    explicit Variable(std::string name, BoxedType type, VariableValue value);
    void print() const;

    std::string name;
    BoxedType type;
    VariableValue value;
  };

}// namespace hasha::lang

#endif//HASHA_VARIABLE_H

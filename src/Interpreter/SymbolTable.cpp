//
// Created by mythi on 19/09/22.
//

#include "SymbolTable.h"
#include "Identifier.h"
#include "fmt/core.h"

namespace hasha {

  SymbolTable::SymbolTable(int level, SymbolTable::Ptr parent)
      : id(generate_uuid()), parent(std::move(parent)), level(level) {
  }

  SymbolTable::Ptr SymbolTable::create(int level, SymbolTable::Ptr parent) {

    return std::make_shared<SymbolTable>(level, std::move(parent));
  }
  
  void SymbolTable::register_varible(const lang::Variable &variable) {

    variables.emplace(variable.name, variable);
  }

  ErrorOr<lang::Variable *> SymbolTable::get_varible(const std::string &key) {

    auto temp = shared_from_this();

    while (temp != nullptr) {
      if (temp->variables.contains(key))
        return &temp->variables.at(key);
      temp = temp->parent;
    }

    return fmt::format("RUNTIME: Failed to access variable {}", key);
  }

  void SymbolTable::register_function(const BoxedFunction &function) {

    functions.insert({function->name()->identifier(), function});
  }

  ErrorOr<BoxedFunction> SymbolTable::get_function(const std::string &key) {

    auto temp = shared_from_this();

    while (temp != nullptr) {
      if (temp->functions.contains(key))
        return temp->functions.at(key);
      temp = temp->parent;
    }

    return fmt::format("RUNTIME: Failed to load function {}", key);
  }


}// namespace hasha
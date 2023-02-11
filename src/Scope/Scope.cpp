//
// Created by mythi on 17/09/22.
//

#include "Scope.h"
#include "Helpers.h"
#include <utility>

namespace hasha {
  Scope::Scope(Ptr parent, int level)
      : parent(std::move(parent)),
        level(level) {
  }

  Scope::Ptr Scope::create(Ptr parent, int level) {

    return std::make_unique<Scope>(std::move(parent), level);
  }

  bool Scope::is_declaration_in_scope(const std::string &name) {

    auto temp = shared_from_this();
    while (temp != nullptr) {
      if (temp->declarations.contains(name) || temp->parameters.contains(name)) {
        return true;
      }
      temp = temp->parent;
    }

    return false;
  }

  bool Scope::is_function_in_scope(const std::string &name) {


    auto temp = shared_from_this();
    while (temp != nullptr) {

      if (temp->functions.contains(name)) {
        return true;
      }
      temp = temp->parent;
    }

    return false;
  }

  const Function *Scope::get_function(const std::string &name) const {

    auto temp = shared_from_this();
    while (temp != nullptr) {

      if (temp->functions.contains(name)) {
        return &*temp->functions.at(name);
      }
      temp = temp->parent;
    }
    return nullptr;
  }

  const Declaration *Scope::get_declaration(const std::string &name) const {

    auto temp = shared_from_this();
    while (temp != nullptr) {

      if (temp->declarations.contains(name)) {
        return &*temp->declarations.at(name);
      }
      temp = temp->parent;
    }

    return nullptr;
  }

  const Parameter *Scope::get_parameter(const std::string &name) const {

    auto temp = shared_from_this();
    while (temp != nullptr) {

      if (temp->parameters.contains(name)) {
        return &*temp->parameters.at(name);
      }
      temp = temp->parent;
    }
    return nullptr;
  }
}// namespace hasha
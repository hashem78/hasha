//
// Created by mythi on 17/09/22.
//

#include "Scope.h"

#include <utility>

namespace hasha {
    Scope::Scope(Ptr parent) : parent(std::move(parent)), id(_id++) {}

    Scope::Ptr Scope::create(Ptr parent) {

        return std::make_unique<Scope>(std::move(parent));
    }

    bool Scope::is_declaration_in_scope(const std::string &name) {

        auto temp = this;
        while (temp != nullptr) {
            if (temp->identifiers.contains(name) || temp->parameters.contains(name)) {
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

    int Scope::_id = 0;

    const Function *Scope::get_function(const std::string &name) const {

        auto temp = shared_from_this();
        while (temp != nullptr) {

            if (temp->functions.contains(name)) {
                return temp->functions.at(name);
            }
            temp = temp->parent;
        }
        return nullptr;
    }

}
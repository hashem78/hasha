//
// Created by mythi on 17/09/22.
//

#include "Scope.h"
#include "fmt/core.h"

namespace hasha {
    Scope::Scope(Scope *parent) : parent(parent), id(_id++) {}

    Scope::Ptr Scope::create(Scope *parent) {

        return std::make_shared<Scope>(parent);
    }

    bool Scope::is_identifier_in_scope(const std::string &name) {

        auto temp = this;
        while (temp != nullptr) {
            if (temp->identifiers.contains(name)) {
                return true;
            }
            temp = temp->parent;
        }

        return false;
    }

    bool Scope::is_function_in_scope(const std::string &name) {


        auto temp = this;
        while (temp != nullptr) {

            if (temp->functions.contains(name)) {
                return true;
            }
            temp = temp->parent;
        }

        return false;
    }

    int Scope::_id = 0;

}
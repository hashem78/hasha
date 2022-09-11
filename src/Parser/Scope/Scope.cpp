//
// Created by mythi on 03/09/22.
//

#include "Scope.h"

namespace hasha {
    Scope::Scope(int owner_id) : owner_id(owner_id), id(id_++) {

    }

    int Scope::id_ = 0;

    Scope::Ptr Scope::create(int owner_id) {

        return std::make_shared<Scope>(owner_id);
    }

    bool Scope::variable_already_defined(std::string_view var_name) const {

        return std::any_of(variables.begin(), variables.end(), [&var_name](const Variable &var) -> bool {
            return var.name == var_name;
        });
    }
} // hasha
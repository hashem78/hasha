//
// Created by mythi on 06/09/22.
//



#include "Variable.h"

namespace hasha {
    int Variable::id_gen = 0;

    Variable::Variable(
            std::string type,
            std::string name,
            std::string value,
            int scope_id
    ) :
            type(std::move(type)),
            name(std::move(name)),
            value(std::move(value)),
            scope_id(scope_id),
            id(id_gen++) {}

}
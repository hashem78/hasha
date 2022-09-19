//
// Created by mythi on 19/09/22.
//

#ifndef HASHA_SYMBOLTABLE_H
#define HASHA_SYMBOLTABLE_H

#include <unordered_map>
#include <string>

#include "ErrorOr.h"

namespace hasha {

    struct VariableValue {
        std::string value;
    };

    class SymbolTable {
        std::unordered_map<std::string, VariableValue> variables;

    public:

        void set_vaiable_value(const std::string &key, const VariableValue &value) {

            variables[key] = value;

        }

        ErrorOr<VariableValue> get_value_for(const std::string &key) const {

            if (!variables.contains(key))
                return "Tried to access variable not in symbol table";

            return variables.at(key);
        }

    };

} // hasha

#endif //HASHA_SYMBOLTABLE_H

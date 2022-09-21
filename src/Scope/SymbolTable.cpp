//
// Created by mythi on 19/09/22.
//

#include "SymbolTable.h"

namespace hasha {

    SymbolTable::SymbolTable(SymbolTable *parent) : id(id_++), parent(parent) {

    }

    SymbolTable::Ptr SymbolTable::create(SymbolTable *parent) {

        return std::make_shared<SymbolTable>(parent);
    }
    void SymbolTable::set_variable_value(const std::string &key, const VariableValue &value) {

        variables[key] = value;

    }

    ErrorOr<VariableValue> SymbolTable::get_value_for(const std::string &key) const {

        if (!variables.contains(key))
            return "Tried to access variable not in symbol table";

        return variables.at(key);
    }

    int SymbolTable::id_ = 0;


} // hasha
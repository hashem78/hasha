//
// Created by mythi on 19/09/22.
//

#include "SymbolTable.h"
#include "fmt/core.h"

namespace hasha {

    SymbolTable::SymbolTable(SymbolTable *parent) : id(id_++), parent(parent) {

    }

    SymbolTable::Ptr SymbolTable::create(SymbolTable *parent) {

        return std::make_shared<SymbolTable>(parent);
    }

    void SymbolTable::set_variable_value(const std::string &key, const HashaVariable &value) {

        variables[key] = value;

    }

    ErrorOr<HashaVariable> SymbolTable::get_value_for(const std::string &key) const {

        if (!variables.contains(key))
            return fmt::format("Tried to access {} not in symbol table {}", key, id);

        return variables.at(key);
    }

    int SymbolTable::id_ = 0;

    void SymbolTable::set_variable_value(const std::string &key, const ExpressionResult &value) {

        set_variable_value(key, HashaVariable{value.res});
    }

    void SymbolTable::set_variable_type(const std::string &key, const HashaVariableType &type) {

        variable_types[key] = type;
    }

    ErrorOr<HashaVariableType> SymbolTable::get_type_for(const std::string &key) const {

        if (!variables.contains(key))
            return "Tried to access variable not in symbol table";

        return variable_types.at(key);

    }


} // hasha
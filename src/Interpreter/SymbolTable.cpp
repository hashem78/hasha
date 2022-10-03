//
// Created by mythi on 19/09/22.
//

#include "SymbolTable.h"
#include "fmt/core.h"

namespace hasha {

    SymbolTable::SymbolTable(SymbolTable::Ptr parent) :
            id(id_++),
            parent(std::move(parent)) {
    }

    SymbolTable::Ptr SymbolTable::create(SymbolTable::Ptr parent) {

        return std::make_shared<SymbolTable>(std::move(parent));
    }

    int SymbolTable::id_ = 0;

    void SymbolTable::register_varible(const lang::Variable &variable) {

        variables.emplace(variable.name, variable);
    }

    lang::Variable &SymbolTable::get_varible(const std::string &key) {

        return variables.at(key);
    }


} // hasha
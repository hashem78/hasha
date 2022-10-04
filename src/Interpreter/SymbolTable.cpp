//
// Created by mythi on 19/09/22.
//

#include "SymbolTable.h"
#include "Identifier.h"
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

    ErrorOr<lang::Variable *> SymbolTable::get_varible(const std::string &key) {

        auto temp = shared_from_this();

        while (temp != nullptr) {
            if (temp->variables.contains(key))
                return &variables.at(key);
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
                return functions.at(key);
            temp = temp->parent;
        }

        return fmt::format("RUNTIME: Failed to load function {}", key);
    }


} // hasha
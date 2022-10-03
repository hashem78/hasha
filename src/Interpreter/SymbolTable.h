//
// Created by mythi on 19/09/22.
//

#ifndef HASHA_SYMBOLTABLE_H
#define HASHA_SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "Language/Variable.h"

#include "ErrorOr.h"


namespace hasha {

    struct SymbolTable {

        using Ptr = std::shared_ptr<SymbolTable>;

        SymbolTable::Ptr parent;
        int id;
        std::vector<Ptr> children;

        explicit SymbolTable(SymbolTable::Ptr parent = nullptr);

        static Ptr create(SymbolTable::Ptr parent = nullptr);

        void register_varible(const lang::Variable &variable);

        lang::Variable &get_varible(const std::string &key);

    private:
        std::unordered_map<std::string, lang::Variable> variables;
        static int id_;
    };

} // hasha

#endif //HASHA_SYMBOLTABLE_H
//
// Created by mythi on 19/09/22.
//

#ifndef HASHA_SYMBOLTABLE_H
#define HASHA_SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "ErrorOr.h"

namespace hasha {

    struct VariableValue {
        std::string value;
    };

    struct SymbolTable {
        std::unordered_map<std::string, VariableValue> variables;
        using Ptr = std::shared_ptr<SymbolTable>;

        SymbolTable *parent;
        int id;
        std::vector<Ptr> children;

        explicit SymbolTable(SymbolTable *parent = nullptr);

        static Ptr create(SymbolTable *parent = nullptr);

        void set_variable_value(const std::string &key, const VariableValue &value);

        ErrorOr<VariableValue> get_value_for(const std::string &key) const;

    private:
        static int id_;
    };

} // hasha

#endif //HASHA_SYMBOLTABLE_H

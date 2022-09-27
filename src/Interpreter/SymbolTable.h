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
#include "HashaVariable.h"
#include "ExpressionResult.h"
#include "HashaVariableType.h"

namespace hasha {

    struct SymbolTable {
        std::unordered_map<std::string, HashaVariable> variables;
        std::unordered_map<std::string, HashaVariableType> variable_types;
        using Ptr = std::shared_ptr<SymbolTable>;

        SymbolTable *parent;
        int id;
        std::vector<Ptr> children;

        explicit SymbolTable(SymbolTable *parent = nullptr);

        static Ptr create(SymbolTable *parent = nullptr);

        void set_variable_value(const std::string &key, const HashaVariable &value);

        void set_variable_type(const std::string &key,const HashaVariableType &type);

        ErrorOr<HashaVariableType> get_type_for(const std::string &key) const;

        void set_variable_value(const std::string &key, const ExpressionResult &value);

        ErrorOr<HashaVariable> get_value_for(const std::string &key) const;

    private:
        static int id_;
    };

} // hasha

#endif //HASHA_SYMBOLTABLE_H

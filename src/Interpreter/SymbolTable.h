//
// Created by mythi on 19/09/22.
//

#ifndef HASHA_SYMBOLTABLE_H
#define HASHA_SYMBOLTABLE_H

#include "Helpers.h"
#include "Language/Variable.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ErrorOr.h"
#include "Function.h"


namespace hasha {

  struct SymbolTable : std::enable_shared_from_this<SymbolTable> {

    using Ptr = std::shared_ptr<SymbolTable>;

    uuid id;
    SymbolTable::Ptr parent;
    std::vector<Ptr> children;
    int level;

    explicit SymbolTable(int level = 0, SymbolTable::Ptr parent = nullptr);

    static Ptr create(int level = 0, SymbolTable::Ptr parent = nullptr);

    void register_varible(const lang::Variable &variable);

    ErrorOr<lang::Variable *> get_varible(const std::string &key);

    void register_function(const BoxedFunction &function);

    ErrorOr<BoxedFunction> get_function(const std::string &key);

   private:
    std::unordered_map<std::string, lang::Variable> variables;
    std::unordered_map<std::string, BoxedFunction> functions;
  };

}// namespace hasha

#endif//HASHA_SYMBOLTABLE_H
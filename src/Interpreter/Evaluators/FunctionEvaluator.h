//
// Created by mythi on 04/10/22.
//

#ifndef HASHA_FUNCTIONEVALUATOR_H
#define HASHA_FUNCTIONEVALUATOR_H

#include "Function.h"
#include "SymbolTableTree.h"
#include "Type/Type.h"

namespace hasha {

  class FunctionEvaluator {

    BoxedFunction function;
    SymbolTableTree::Ptr symbol_tree;
    SymbolTable::Ptr symbol_table;

   public:
    explicit FunctionEvaluator(
      BoxedFunction function,
      SymbolTableTree::Ptr symbol_tree,
      SymbolTable::Ptr symbol_table

    ) noexcept;

    ErrorOr<lang::VariableValue> evaluate();
  };

}// namespace hasha

#endif//HASHA_FUNCTIONEVALUATOR_H

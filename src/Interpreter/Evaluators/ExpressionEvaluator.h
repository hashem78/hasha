//
// Created by mythi on 03/10/22.
//

#ifndef HASHA_EXPRESSIONEVALUATOR_H
#define HASHA_EXPRESSIONEVALUATOR_H

#include "ErrorOr.h"
#include "Expression.h"
#include "SymbolTable.h"
#include "SymbolTableTree.h"
#include "Type/GenericType.h"
#include "Type/NormalType.h"

namespace hasha {

  struct ExpressionEvaluator {
    BoxedExpression expression;
    SymbolTableTree::Ptr symbol_tree;
    SymbolTable::Ptr symbol_table;
    std::variant<Box<NormalType>,Box<GenericType>> expected_type;

    explicit ExpressionEvaluator(
      BoxedExpression expression,
      SymbolTableTree::Ptr symbol_tree,
      SymbolTable::Ptr symbol_table,
      std::variant<Box<NormalType>,Box<GenericType>> expected_type
    ) noexcept;

    [[nodiscard]] ErrorOr<lang::VariableValue> evaluate() const;
  };

}// namespace hasha

#endif//HASHA_EXPRESSIONEVALUATOR_H

//
// Created by mythi on 03/10/22.
//

#ifndef HASHA_EXPRESSIONEVALUATOR_H
#define HASHA_EXPRESSIONEVALUATOR_H

#include "Expression.h"
#include "SymbolTable.h"
#include "ErrorOr.h"
#include "SymbolTableTree.h"

namespace hasha {

    struct ExpressionEvaluator {
        BoxedExpression expression;
        SymbolTable::Ptr symbol_table;
        SymbolTableTree::Ptr symbol_tree;

        explicit ExpressionEvaluator(
                BoxedExpression expression,
                SymbolTableTree::Ptr symbol_tree,
                SymbolTable::Ptr symbol_table
        ) noexcept;

        [[nodiscard]]
        ErrorOr<lang::VariableValue> evaluate() const;

    };

} // hasha

#endif //HASHA_EXPRESSIONEVALUATOR_H

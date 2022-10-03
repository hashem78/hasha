//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_GLOBALBLOCKVISITOR_H
#define HASHA_GLOBALBLOCKVISITOR_H

#include <utility>

#include "Identifier.h"
#include "Type/Type.h"
#include "Type/GenericType.h"
#include "Type/NormalType.h"
#include "Declaration.h"
#include "Expression.h"
#include "Literal.h"
#include "Operator.h"
#include "FunctionCall.h"
#include "Block.h"
#include "Assignment.h"
#include "Function.h"
#include "Parameter.h"
#include "Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "fmt/core.h"
#include "ErrorOr.h"
#include "ScopeTree.h"
#include "SymbolTableTree.h"
#include "ExpressionEvaluator.h"

namespace hasha {

    struct GlobalBlockVisitor {


        Scope::Ptr scope;
        SymbolTable::Ptr symbol_table;

        ScopeTree::Ptr scope_tree;
        SymbolTableTree::Ptr symbol_table_tree;

        explicit GlobalBlockVisitor(
                Scope::Ptr scope,
                SymbolTable::Ptr symbol_table,
                ScopeTree::Ptr scope_tree,
                SymbolTableTree::Ptr symbol_table_tree
        ) :
                scope(std::move(scope)),
                symbol_table(std::move(symbol_table)),
                scope_tree(std::move(scope_tree)),
                symbol_table_tree(std::move(symbol_table_tree)) {

        }

        [[nodiscard]]
        ErrorOr<void> operator()(auto) const noexcept {

            return {};
        }

        [[nodiscard]]
        ErrorOr<void> operator()(const BoxedDeclaration &obj) const noexcept {

            auto evaluator = ExpressionEvaluator{obj->assignment_expression(), symbol_table};

            symbol_table->register_varible(lang::Variable{obj->name()->identifier(), TRY(evaluator.evaluate())});
            symbol_table->get_varible(obj->name()->identifier()).print();
            return {};
        }

        [[nodiscard]]
        ErrorOr<void> operator()(const BoxedFunction &obj) const noexcept {

            return {};
        }
    };

} // hasha

#endif //HASHA_GLOBALBLOCKVISITOR_H

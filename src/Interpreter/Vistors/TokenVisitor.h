//
// Created by mythi on 03/10/22.
//

#ifndef HASHA_TOKENVISITOR_H
#define HASHA_TOKENVISITOR_H

#include "SymbolTableTree.h"
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
#include "Block.h"
#include "Function.h"
#include "Parameter.h"
#include "Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "Evaluators/ExpressionEvaluator.h"

namespace hasha {

    struct TokenVisitor {
        SymbolTableTree::Ptr symbol_tree;
        SymbolTable::Ptr symbol_table;

        ErrorOr<void> operator()(auto) {

            return {};
        }

        ErrorOr<void> operator()(const BoxedDeclaration &obj) {

            auto evaluator = ExpressionEvaluator{
                    obj->assignment_expression(),
                    symbol_tree,
                    symbol_table
            };
            auto assignment_value = TRY(evaluator.evaluate());
            auto variable = lang::Variable{obj->name()->identifier(), assignment_value};
            symbol_table->register_varible(variable);
            variable.print();

            return {};
        }

        ErrorOr<void> operator()(const BoxedExpression &obj) const {

            auto evaluator = ExpressionEvaluator{
                    obj,
                    symbol_tree,
                    symbol_table
            };
            auto value = TRY(evaluator.evaluate());

            // TODO: Expressions should have side effects

            return {};
        }

        ErrorOr<void> operator()(const BoxedFunctionCall &obj) {

            // TODO: FunctionCalls should have side effects

            return {};
        }

        ErrorOr<void> operator()(const BoxedAssignment &obj) {

            auto evaluator = ExpressionEvaluator{
                    obj->expression(),
                    symbol_tree,
                    symbol_table
            };
            auto value = TRY(evaluator.evaluate());
            auto var_name = obj->assignee()->identifier();
            TRY(symbol_table->get_varible(var_name))->value = value;

            return {};
        }

        ErrorOr<void> operator()(const BoxedBlock &obj) {

            auto block_symbol_table = symbol_tree->create_table(symbol_table);

            for (const auto &token: obj->tokens()) {
                TRY(std::visit(TokenVisitor{symbol_tree, block_symbol_table}, token));
            }
            return {};
        }

        ErrorOr<void> operator()(const BoxedIfStatement &obj) {

            return {};
        }

        ErrorOr<void> operator()(const BoxedElifStatement &obj) {

            return {};
        }

        ErrorOr<void> operator()(const BoxedElseStatement &obj) {

            return {};
        }
    };

} // hasha

#endif //HASHA_TOKENVISITOR_H

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

        ErrorOr<void> operator()(const BoxedDeclaration &obj);

        ErrorOr<void> operator()(const BoxedExpression &obj) const;

        ErrorOr<void> operator()(const BoxedFunctionCall &obj);

        ErrorOr<void> operator()(const BoxedAssignment &obj);

        ErrorOr<void> operator()(const BoxedBlock &obj);

        ErrorOr<void> operator()(const BoxedIfStatement &obj);

        ErrorOr<void> operator()(const BoxedElifStatement &obj);

        ErrorOr<void> operator()(const BoxedElseStatement &obj);
    };

} // hasha

#endif //HASHA_TOKENVISITOR_H

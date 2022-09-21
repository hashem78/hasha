//
// Created by mythi on 21/09/22.
//

#ifndef HASHA_TYPECHECKER_H
#define HASHA_TYPECHECKER_H

#include <stack>

#include "ErrorOr.h"
#include "Type/Type.h"
#include "Expression/Expression.h"
#include "Literal/Literal.h"
#include "FunctionCall.h"
#include "Declaration.h"

#include "Function.h"

namespace hasha {


    class TypeChecker {
        std::stack<Type> types;
        const Scope &scope;

        [[nodiscard]]
        const Type &current_type() const;

        void set_type(const Type &type);

        void restore_type();

    public:
        explicit TypeChecker(const Type &type, const Scope &scope);

        ErrorOr<void> check_declaration(
                const Declaration &declaration
        );

        ErrorOr<void> check_expression(
                const Expression &expression

        );

        ErrorOr<void> check_literal(
                const Literal &literal
        );

        ErrorOr<void> check_function_call(
                const FunctionCall &function_call
        );


    };

} // hasha

#endif //HASHA_TYPECHECKER_H

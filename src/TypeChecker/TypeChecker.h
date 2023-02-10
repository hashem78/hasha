//
// Created by mythi on 21/09/22.
//

#ifndef HASHA_TYPECHECKER_H
#define HASHA_TYPECHECKER_H

#include "Declaration.h"
#include "ErrorOr.h"
#include "Expression.h"
#include "FunctionCall.h"
#include "Identifier.h"
#include "Literal.h"
#include "Scope.h"
#include "Type/Type.h"

namespace hasha {


  class TypeChecker {
    BoxedType type;
    const Scope::Ptr scope;

   public:
    explicit TypeChecker(BoxedType type, Scope::Ptr scope);

    ErrorOr<void> check_declaration(
      const BoxedDeclaration &declaration
    );

    ErrorOr<void> check_expression(
      const BoxedExpression &expression

    );

    ErrorOr<void> check_identifier(
      const BoxedIdentifier &identifier
    );

    ErrorOr<void> check_literal(
      const BoxedLiteral &literal
    );

    ErrorOr<void> check_function_call(
      const BoxedFunctionCall &function_call
    );
  };

}// namespace hasha

#endif//HASHA_TYPECHECKER_H
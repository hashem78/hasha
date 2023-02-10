//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_JSONCONVERTER_H
#define HASHA_JSONCONVERTER_H

#include "Assignment.h"
#include "Block.h"
#include "Declaration.h"
#include "Expression.h"
#include "Function.h"
#include "FunctionCall.h"
#include "Identifier.h"
#include "Literal.h"
#include "Operator.h"
#include "Parameter.h"
#include "ReturnToken.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "Statement/IfStatement.h"
#include "Type/GenericType.h"
#include "Type/NormalType.h"
#include "Type/Type.h"
#include "fmt/core.h"
#include "magic_enum.hpp"
#include "nlohmann/json.hpp"

namespace hasha {

  struct JsonConverter {
    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedNormalType &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedGenericType &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedIdentifier &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedType &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedDeclaration &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedExpression &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedLiteral &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedOperator &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedFunctionCall &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedBlock &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedAssignment &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedFunction &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedParameter &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedIfStatement &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedElifStatement &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedElseStatement &obj) const noexcept;

    [[nodiscard]] nlohmann::ordered_json operator()(const BoxedReturnToken &obj) const noexcept;
  };

}// namespace hasha

#endif//HASHA_JSONCONVERTER_H

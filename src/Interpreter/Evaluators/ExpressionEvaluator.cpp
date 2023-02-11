//
// Created by mythi on 03/10/22.
//

#include "ExpressionEvaluator.h"
#include "FunctionCall.h"
#include "FunctionEvaluator.h"
#include "Identifier.h"
#include "Literal.h"
#include "Operator.h"
#include "Overload.h"
#include "Type/DefaultParserTypes.h"
#include "Type/Type.h"
#include "Vistors/BoxedTypeStringifier.h"
#include "Vistors/TokenVisitor.h"
#include "fmt/core.h"
#include "fmt/std.h"
#include <stack>
#include <variant>

namespace hasha {
  ExpressionEvaluator::ExpressionEvaluator(
    BoxedExpression expression,
    SymbolTableTree::Ptr symbol_tree,
    SymbolTable::Ptr symbol_table,
    std::variant<Box<NormalType>, Box<GenericType>> expected_type
  ) noexcept
      : expression(std::move(expression)),
        symbol_tree(std::move(symbol_tree)),
        symbol_table(std::move(symbol_table)),
        expected_type(std::move(expected_type)) {
  }

  ErrorOr<lang::VariableValue> ExpressionEvaluator::evaluate() const {

    std::stack<lang::VariableValue> stk;
    for (const auto &token: expression->expression()) {
      TRYV(
        token,
        [&, this](const BoxedExpression &expr) -> ErrorOr<void> {
          auto evaluator = ExpressionEvaluator{
            expr,
            symbol_tree,
            symbol_table,
            expected_type};
          stk.push(TRY(evaluator.evaluate()));
          return {};
        },
        [&, this](const BoxedIdentifier &identifier) -> ErrorOr<void> {
          stk.push(TRY(symbol_table->get_varible(identifier->identifier()))->value);
          return {};
        },
        [&](const BoxedOperator &op) -> ErrorOr<void> {
          lang::VariableValue result{};
          switch (op->type()) {

            case OperatorType::Unary: {
              auto a = stk.top();
              stk.pop();
              if (op->operation() == "-") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](int i) { return -i; },
                    [](float f) { return -f; },
                    [](auto z) { return z; }},
                  a
                );
              }
            } break;
            case OperatorType::Binary: {
              auto b = stk.top();
              stk.pop();
              auto a = stk.top();
              stk.pop();
              if (op->operation() == "-") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](int i1, auto i2) { return i1 - i2; },
                    [](float f1, auto f2) { return f1 - f2; },
                    [](auto z) { return z; }},
                  a,
                  b
                );
              } else if (op->operation() == "+") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](int i1, auto i2) { return i1 + i2; },
                    [](float f1, auto f2) { return f1 + f2; },
                    [](auto z) { return z; }},
                  a,
                  b
                );
              } else if (op->operation() == "*") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](int i1, auto i2) { return i1 * i2; },
                    [](float f1, auto f2) { return f1 * f2; },
                    [](auto z) { return z; }},
                  a,
                  b
                );
              } else if (op->operation() == "/") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](int i1, auto i2) { return i1 / i2; },
                    [](float f1, auto f2) { return f1 / f2; },
                    [](auto z) { return z; }},
                  a,
                  b
                );
              } else if (op->operation() == "&&") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](bool i1, bool i2) { return i1 && i2; },
                    [](auto) { return true; }},
                  a,
                  b
                );
              } else if (op->operation() == "||") {
                result = std::visit<lang::VariableValue>(
                  Overload{
                    [](bool i1, bool i2) { return i1 || i2; },
                    [](auto) { return true; }},
                  a,
                  b
                );
              }
            } break;
            case OperatorType::Ternary:
              break;
          }
          stk.push(result);
          return {};
        },
        [&](const BoxedLiteral &literal) -> ErrorOr<void> {
          lang::VariableValue val{};
          switch (literal->type()) {

            case LiteralType::Integer:
              val = std::stoi(literal->literal());
              break;
            case LiteralType::Float:
              val = std::stof(literal->literal());
              break;
            case LiteralType::String:
              break;
            case LiteralType::Boolean:
              if (literal->literal() == "false") {
                val = false;
              } else {
                val = true;
              }
              break;
          }
          stk.push(val);
          return {};
        },
        [&, this](const BoxedFunctionCall &function_call) -> ErrorOr<void> {
          auto call_name = function_call->callee();
          auto call_arguments = function_call->arguments();

          auto function = TRY(symbol_table->get_function(call_name));
          auto function_parameters = function->parameters();

          TRYV2(
            function->return_type(),
            expected_type,
            [&](const BoxedNormalType &a, const BoxedGenericType &b) -> ErrorOr<void> {
              return fmt::format(
                "Return type of {} is {}, expected {} in this context on line: {}, col: {}",
                call_name,
                a->type(),
                std::visit(BoxedTypeToString{}, b->type()),
                b->details().span.line,
                b->details().span.col
              );
            },
            [&](const BoxedGenericType &a, const BoxedNormalType &b) -> ErrorOr<void> {
              return fmt::format(
                "Return type of {} is {}, expected {} in this context on line: {}, col: {}",
                call_name,
                std::visit(BoxedTypeToString{}, a->type()),
                b->type(),
                b->details().span.line,
                b->details().span.col
              );
            },
            [&](const BoxedGenericType &a, const BoxedGenericType &b) -> ErrorOr<void> {
              if (*a != *b) {
                return fmt::format(
                  "Return type of {} is {}, expected {} in this context on line: {}, col: {}",
                  call_name,
                  std::visit(BoxedTypeToString{}, a->type()),
                  std::visit(BoxedTypeToString{}, b->type()),
                  b->details().span.line,
                  b->details().span.col
                );
              }
              return {};
            },
            [&](const BoxedNormalType &a, const BoxedNormalType &b) -> ErrorOr<void> {
              if (*a != *b) {
                return fmt::format(
                  "Return type of {} is {}, expected {} in this context on line: {}, col: {}",
                  call_name,
                  a->type(),
                  b->type(),
                  b->details().span.line,
                  b->details().span.col
                );
              }
              return {};
            }

          );

          if (call_arguments.size() != function_parameters.size()) {
            return fmt::format(
              "{} expects {} got {} arguments on line: {}, col: {}",
              call_name,
              function_parameters.size(),
              call_arguments.size(),
              function_call->details().span.line,
              function_call->details().span.col
            );
          }
          // Register parameters with evaled arguments
          int arg_index = 0;
          auto sym_t = symbol_tree->create_table(symbol_table);
          for (const auto &arg_expression: call_arguments) {
            auto evaluator = ExpressionEvaluator{
              arg_expression,
              symbol_tree,
              sym_t,
              expected_type};
            auto val = TRY(evaluator.evaluate());
            auto val_type = std::visit(
              Overload{
                [](int) { return DefIntegerType; },
                [](float) { return DefFloatingPointType; },
                [](bool) { return DefBooleanType; }},
              val
            );
            auto param_name = function_parameters[arg_index++]->name()->identifier();
            auto variable = lang::Variable{param_name, val_type, val};
            sym_t->register_varible(variable);
          }
          auto evaluator = FunctionEvaluator{
            function,
            symbol_tree,
            sym_t};
          auto val = TRY(evaluator.evaluate());
          stk.push(val);
          return {};
        }
      );
    }
    return stk.top();
  }
}// namespace hasha
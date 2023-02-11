//
// Created by mythi on 03/10/22.
//

#include "TokenVisitor.h"
#include "Overload.h"
#include "Type/DefaultParserTypes.h"

namespace hasha {
  ErrorOr<void> TokenVisitor::operator()(const BoxedDeclaration &obj) {

    auto evaluator = ExpressionEvaluator{
      obj->assignment_expression(),
      symbol_tree,
      symbol_table,
      obj->type()};
    auto assignment_value = TRY(evaluator.evaluate());
    auto variable = lang::Variable{
      obj->name()->identifier(),
      obj->type(),
      assignment_value};
    symbol_table->register_varible(variable);
    variable.print();

    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedExpression &) const {

    // auto evaluator = ExpressionEvaluator{
    //   obj,
    //   symbol_tree,
    //   symbol_table,
    //   };

    // TODO: Expressions should have side effects

    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedFunctionCall &) {

    // TODO: FunctionCalls should have side effects

    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedAssignment &obj) {

    auto var_name = obj->assignee()->identifier();
    auto var = TRY(symbol_table->get_varible(var_name));

    auto evaluator = ExpressionEvaluator{
      obj->expression(),
      symbol_tree,
      symbol_table,
      var->type};
    auto value = TRY(evaluator.evaluate());
    var->value = value;

    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedBlock &obj) {

    auto block_symbol_table = symbol_tree->create_table(symbol_table);

    for (const auto &token: obj->tokens()) {
      TRYV(
        token,
        TokenVisitor{symbol_tree, block_symbol_table}
      );
    }
    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedIfStatement &obj) {
    auto evaluator = ExpressionEvaluator{
      obj->condition(),
      symbol_tree,
      symbol_table,
      DefBooleanType};
    auto condition = std::get<bool>(TRY(evaluator.evaluate()));
    if (condition) {

      auto block_symbol_table = symbol_tree->create_table(symbol_table);

      for (const auto &token: obj->block()->tokens()) {
        TRYV(
          token,
          TokenVisitor{symbol_tree, block_symbol_table}
        );
      }
    }
    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedElifStatement &) {

    return {};
  }

  ErrorOr<void> TokenVisitor::operator()(const BoxedElseStatement &) {

    return {};
  }
}// namespace hasha
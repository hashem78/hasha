//
// Created by mythi on 02/10/22.
//

#include "Interpreter.h"
#include "Declaration.h"
#include "Evaluators/ExpressionEvaluator.h"
#include "Identifier.h"
#include "Overload.h"
#include "Vistors/TokenVisitor.h"

namespace hasha {
  Interpreter::Interpreter(
    BoxedBlock block,
    ScopeTree::Ptr scope_tree,
    Scope::Ptr global_scope
  ) noexcept
      : global_block(std::move(block)),
        scope_tree(std::move(scope_tree)),
        global_scope(std::move(global_scope)),
        symbol_table_tree(SymbolTableTree::create()) {
  }

  ErrorOr<void> Interpreter::interpret() {

    TRY(first_pass());
    TRY(second_pass());

    return {};
  }

  ErrorOr<void> Interpreter::first_pass() {

    auto global_symbol_table = symbol_table_tree->global_symbol_table();

    for (const auto &token: global_block->tokens()) {

      TRY(
        std::visit(
          Overload{
            [&](const BoxedDeclaration &obj) noexcept -> ErrorOr<void> {
              auto evaluator = ExpressionEvaluator{
                obj->assignment_expression(),
                symbol_table_tree,
                global_symbol_table};
              auto assignment_value = TRY(evaluator.evaluate());
              auto variable = lang::Variable{obj->name()->identifier(), assignment_value};
              global_symbol_table->register_varible(variable);

              return {};
            },
            [&](const BoxedFunction &obj) noexcept -> ErrorOr<void> {
              global_symbol_table->register_function(obj);

              return {};
            },
            [](auto) -> ErrorOr<void> { return {}; }},
          token
        )
      );
    }
    return {};
  }

  ErrorOr<void> Interpreter::second_pass() {

    auto global_symbol_table = symbol_table_tree->global_symbol_table();
    auto main_function = TRY(global_symbol_table->get_function("main"));
    for (const auto &token: main_function->block()->tokens()) {

      TRY(
        std::visit(
          TokenVisitor{
            symbol_table_tree,
            global_symbol_table},
          token
        )
      );
    }

    return {};
  }
}// namespace hasha
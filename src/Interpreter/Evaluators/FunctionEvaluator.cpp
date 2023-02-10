//
// Created by mythi on 04/10/22.
//

#include "FunctionEvaluator.h"
#include "Block.h"
#include "ReturnToken.h"
#include "Vistors/TokenVisitor.h"

namespace hasha {

  FunctionEvaluator::FunctionEvaluator(
    BoxedFunction function,
    SymbolTableTree::Ptr symbol_tree,
    SymbolTable::Ptr symbol_table
  ) noexcept
      : function(std::move(function)),
        symbol_tree(std::move(symbol_tree)),
        symbol_table(std::move(symbol_table)) {
  }

  ErrorOr<lang::VariableValue> FunctionEvaluator::evaluate() {

    for (const auto &token: function->block()->tokens()) {
      if (holds_alternative<BoxedReturnToken>(token)) {
        auto return_expression = std::get<BoxedReturnToken>(token)->expression();
        auto evaluator = ExpressionEvaluator{return_expression, symbol_tree, symbol_table};
        auto res = TRY(evaluator.evaluate());
        return res;
      }
      TRY(std::visit(TokenVisitor{symbol_tree, symbol_table}, token));
    }
    return {};
  }

}// namespace hasha
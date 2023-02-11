//
// Created by mythi on 04/10/22.
//

#include "FunctionEvaluator.h"
#include "Block.h"
#include "Overload.h"
#include "ReturnToken.h"
#include "Token.h"
#include "Vistors/TokenVisitor.h"
#include <optional>

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

      if (auto return_token = token.as<ReturnToken>()) {
        auto return_expression = EXTRACT(return_token)->expression();
        auto evaluator = ExpressionEvaluator{
          return_expression,
          symbol_tree,
          symbol_table,
          function->return_type()};
        return TRY(evaluator.evaluate());
      }
      TRYV(
        token,
        TokenVisitor{symbol_tree, symbol_table}
      );
    }
    return {};
  }

}// namespace hasha
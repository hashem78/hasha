//
// Created by mythi on 03/10/22.
//

#include <stack>
#include "ExpressionEvaluator.h"
#include "Overload.h"
#include "Identifier.h"
#include "Operator.h"
#include "Literal.h"

namespace hasha {
    ExpressionEvaluator::ExpressionEvaluator(
            BoxedExpression expression,
            SymbolTable::Ptr symbol_table
    ) noexcept:
            expression(std::move(expression)),
            symbol_table(std::move(symbol_table)) {
    }

    ErrorOr<lang::VariableValue> ExpressionEvaluator::evaluate() const {

        std::stack<lang::VariableValue> stk;
        for (const auto &token: expression->expression()) {
            TRY(
                    std::visit(
                            Overload{
                                    [](auto) -> ErrorOr<void> { return {}; },
                                    [&, this](const BoxedIdentifier &identifier) -> ErrorOr<void> {
                                        stk.push(symbol_table->get_varible(identifier->identifier()).value);
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
                                                                    [](auto z) { return z; }
                                                            }, a
                                                    );
                                                }
                                            }
                                                break;
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
                                                                    [](auto z) { return z; }
                                                            }, a, b
                                                    );
                                                } else if (op->operation() == "+") {
                                                    result = std::visit<lang::VariableValue>(
                                                            Overload{
                                                                    [](int i1, auto i2) { return i1 + i2; },
                                                                    [](float f1, auto f2) { return f1 + f2; },
                                                                    [](auto z) { return z; }
                                                            }, a, b
                                                    );
                                                } else if (op->operation() == "*") {
                                                    result = std::visit<lang::VariableValue>(
                                                            Overload{
                                                                    [](int i1, auto i2) { return i1 * i2; },
                                                                    [](float f1, auto f2) { return f1 * f2; },
                                                                    [](auto z) { return z; }
                                                            }, a, b
                                                    );
                                                } else if (op->operation() == "/") {
                                                    result = std::visit<lang::VariableValue>(
                                                            Overload{
                                                                    [](int i1, auto i2) { return i1 / i2; },
                                                                    [](float f1, auto f2) { return f1 / f2; },
                                                                    [](auto z) { return z; }
                                                            }, a, b
                                                    );
                                                }
                                            }
                                                break;
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
                                    }
                            }, token
                    )
            );
        }
        return stk.top();
    }
} // hasha
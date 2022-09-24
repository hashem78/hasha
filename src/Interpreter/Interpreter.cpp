//
// Created by mythi on 03/09/22.
//

#include <stack>

#include "Interpreter.h"
#include "FunctionCall.h"
#include "TypeChecker.h"
#include "Literal/NumericLiteral.h"
#include "Literal/BooleanLiteral.h"
#include "Literal/StringLiteral.h"
#include "Operator/UnaryOperator.h"
#include "Operator/BinaryOperator.h"

namespace hasha::interpeter {
    Interpreter::Interpreter(
            Block::Ptr block,
            ScopeTree::Ptr scope_tree
    ) :
            global_block(std::move(block)),
            scope_tree(std::move(scope_tree)),
            symbol_tree(std::move(SymbolTree::create())) {
    }

    ErrorOr<void> Interpreter::interpret_if(const IfStatement &if_statement, SymbolTable &table) {

        return {};
    }

    ErrorOr<void> Interpreter::interpret_elif(const ElifStatement &elif_statement, SymbolTable &table) {

        return {};
    }

    ErrorOr<void> Interpreter::interpret_else(const ElseStatement &else_statement, SymbolTable &table) {

        return {};
    }

    ErrorOr<ExpressionResult> Interpreter::interpret_expression(const Expression &expression, SymbolTable &table) {

        // Expression can be of type ReturnExpression
        std::stack<int> stk;

        for (const auto &token: expression.expression_tokens()) {

            // FunctionCall
            if (auto function_call = dynamic_cast<FunctionCall *>(token.get())) {

            }

            // Unary O`perator
            if (auto op = dynamic_cast<UnaryOperator *>(token.get())) {
                if (op->operation() == "-") {
                    stk.top() = stk.top() * -1;
                }
            }

            // Binary Operator
            if (auto op = dynamic_cast<BinaryOperator *>(token.get())) {
                if (op->operation() == "*") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();

                    stk.push(a * b);
                } else if (op->operation() == "/") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();

                    stk.push(a / b);
                }
                if (op->operation() == "+") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();

                    stk.push(a + b);
                } else if (op->operation() == "-") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();

                    stk.push(a - b);
                }
            }

            // NumericLiteral
            if (auto numeric_literal = dynamic_cast<NumericLiteral *>(token.get())) {

                stk.push(std::stoi(numeric_literal->get_literal()));
            }
            // StringLiteral
            if (auto string_literal = dynamic_cast<StringLiteral *>(token.get())) {

            }
            // BooleanLiteral
            if (auto boolean_literal = dynamic_cast<BooleanLiteral *>(token.get())) {

            }
            // Identifier
            if (auto identifier = dynamic_cast<Identifier *>(token.get())) {

                const auto &val = TRY(table.get_value_for(identifier->get())).value;
                stk.push(std::stoi(val));
            }
        }
        if (stk.empty())
            return "Failed to parse expression";

        return ExpressionResult{std::to_string(stk.top())};
    }

    ErrorOr<void> Interpreter::interpret_declaration(const Declaration &declaration, SymbolTable &table) {

        const auto &scope = *scope_tree->get_by_id(declaration.scope_id());
        TypeChecker type_checker(declaration.type(), scope);
        TRY(type_checker.check_declaration(declaration));
        auto result = TRY(interpret_expression(declaration.assignment_expression(), table));
        const auto &name = declaration.name().get();
        const auto &type = declaration.type().get_type();
        fmt::print("Declaration: Set {} to {}\n", name, result.res);
        table.set_variable_type(name, HashaVariableType{type});
        table.set_variable_value(name, result);

        return {};
    }

    ErrorOr<void> Interpreter::interpret_function(const Function &function, SymbolTable &table) {

        TRY(interpret_block(function.block(), table));

        return {};
    }

    ErrorOr<void> Interpreter::interpret_block(const Block &block, SymbolTable &table) {

        auto new_table = symbol_tree->create_table(table.id);

        for (const auto &block_token: block.get_tokens()) {
            if (auto decl = dynamic_cast<Declaration *>(block_token.get())) {
                TRY(interpret_declaration(*decl, new_table));
            } else if (auto assignment = dynamic_cast<Assignment *>(block_token.get())) {
                TRY(interpret_assignment(*assignment, new_table));
            } else if (auto if_st = dynamic_cast<IfStatement *>(block_token.get())) {
                TRY(interpret_if(*if_st, new_table));
            } else if (auto elif_st = dynamic_cast<ElifStatement *>(block_token.get())) {
                TRY(interpret_elif(*elif_st, new_table));
            } else if (auto else_st = dynamic_cast<ElseStatement *>(block_token.get())) {
                TRY(interpret_else(*else_st, new_table));
            }
        }
        return {};
    }

    ErrorOr<void> Interpreter::interpret() {

        auto global_symbol_table = symbol_tree->create_table();
        for (const auto &block_token: global_block->get_tokens()) {
            if (auto fn = dynamic_cast<Function *>(block_token.get())) {
                TRY(interpret_function(*fn, global_symbol_table));
            }
        }

        return {};
    }

    ErrorOr<void> Interpreter::interpret_assignment(const Assignment &assignment, SymbolTable &table) {

        const auto &scope = scope_tree->get_by_id(assignment.scope_id());
        auto res = TRY(interpret_expression(assignment.expression(), table));
        table.set_variable_value(assignment.assignee().get(), res);
        fmt::print("Set {} to {}\n", assignment.assignee().get(), res.res);
        return {};
    }


} // hasha
//
// Created by mythi on 01/09/22.
//

#include <stack>

#include "Expression.h"
#include "Literal/NumericLiteral.h"
#include "Operator.h"
#include "Identifier.h"

namespace hasha {
    nlohmann::json Expression::to_json() const {

        return {
                {"token_type", "Expression"},
                {"expression", token_list_to_json(expression)},
                {"span",       m_span.to_json()}
        };
    }

    Expression::Ptr Expression::create(TokenList expr, const Span &span, int scope_id) {

        return std::make_unique<Expression>(std::move(expr), span, scope_id);
    }

    Expression::Expression(
            TokenList expr,
            const Span &span, int scope_id
    ) :
            expression(std::move(expr)),
            Token(span, scope_id) {
    }

    std::string Expression::evaluate(const Scope &scope) const {

        std::stack<int> stk;

        for (const auto &token: expression) {
            if (auto number = dynamic_cast<NumericLiteral *>(token.get())) {
                // fmt::print("{}\n",number->to_string());
                stk.push(std::stoi(number->get_literal()));
            } else if (auto operation = dynamic_cast<Operator *>(token.get())) {
                // fmt::print("{}\n",operation->to_string());
                const auto &op = operation->get_op();
                if (op == "+") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();
                    stk.push(a + b);
                } else if (op == "-") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();
                    stk.push(a - b);
                } else if (op == "*") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();
                    stk.push(a * b);
                } else if (op == "/") {
                    auto b = stk.top();
                    stk.pop();
                    auto a = stk.top();
                    stk.pop();
                    stk.push(a / b);
                }
            } else if (auto identifier = dynamic_cast<Identifier *>(token.get())) {
                auto val = TRY(scope.symbol_table.get_value_for(identifier->get()));
                stk.push(std::stoi(val.value));
            }
        }
        // TODO: Implement function calls in expressions
        if (stk.empty())
            return std::string{};

        return std::to_string(stk.top());
    }

    bool Expression::empty() const {

        return expression.empty();
    }

    const TokenList &Expression::get_expression_tokens() const {

        return expression;
    }

    nlohmann::json expression_list_to_json(const ExpressionList &expression_list) {

        auto arr = nlohmann::json::array();
        for (const auto &expr: expression_list) {
            arr.push_back(expr->to_json());
        }
        return arr;
    }
} // hasha
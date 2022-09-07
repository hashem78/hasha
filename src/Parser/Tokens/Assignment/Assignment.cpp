//
// Created by mythi on 01/09/22.
//

#include <stack>
#include "Assignment.h"
#include "Literal/NumericLiteral.h"
#include "Operator.h"

namespace hasha {
    nlohmann::json Assignment::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Assignment";
        json["expression"] = expression->to_json();
        json["span"] = m_span.to_json();
        return json;
    }

    Assignment::Assignment(
            Expression::Ptr expression,
            const Span &span
    ) :
            expression(std::move(expression)),
            Token(span) {
    }

    Assignment::Ptr Assignment::create(
            Expression::Ptr expression,
            const Span &span
    ) {

        return std::make_unique<Assignment>(std::move(expression), span);
    }

    std::string Assignment::calculate() const {

        std::stack<int> stk;
        for (const auto &token: *expression->get_expression()) {
            if (auto number = dynamic_cast<NumericLiteral *>(token.get())) {
                fmt::print("{}\n",number->to_string());
                stk.push(std::stoi(number->get_literal()));
            } else if (auto operation = dynamic_cast<Operator *>(token.get())) {
                fmt::print("{}\n",operation->to_string());
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
            }
        }
        return std::to_string(stk.top());
    }
} // hasha
//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_NUMERICOPERATOR_H
#define HASHA_NUMERICOPERATOR_H

#include "Operator.h"

namespace hasha {

    class NumericOperator : public Operator {
        using Operator::Operator;

    public:
        using NumericOperatorPtr = std::shared_ptr<NumericOperator>;

        static NumericOperatorPtr create(std::string op) {

            return std::make_shared<NumericOperator>(std::move(op));
        }

        [[nodiscard]]
        nlohmann::json to_json() const override {

            return {
                    {"token_type", "NumericOperator"},
                    {"operator",   m_op}
            };
        }

        [[nodiscard]]
        std::string to_string() const override {

            return fmt::format("NumericOperator {}", m_op);
        }
    };

} // hasha

#endif //HASHA_NUMERICOPERATOR_H

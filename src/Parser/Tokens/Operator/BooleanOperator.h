//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_BOOLEANOPERATOR_H
#define HASHA_BOOLEANOPERATOR_H

#include "Operator.h"

namespace hasha {

    class BooleanOperator : public Operator {
        using Operator::Operator;

    public:
        using BooleanOperatorPtr = std::unique_ptr<BooleanOperator>;

        static BooleanOperatorPtr create(std::string op) {

            return std::make_unique<BooleanOperator>(std::move(op));
        }

        [[nodiscard]]
        nlohmann::json to_json() const override {

            return {
                    {"token_type", "BooleanOperator"},
                    {"operator",   m_op}
            };
        }

        [[nodiscard]]
        std::string to_string() const override {

            return fmt::format("BooleanOperator {}", m_op);
        }
    };

} // hasha

#endif //HASHA_BOOLEANOPERATOR_H

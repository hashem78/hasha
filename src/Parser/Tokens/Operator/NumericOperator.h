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
        using Ptr = std::unique_ptr<NumericOperator>;

        static Ptr create(std::string op);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_NUMERICOPERATOR_H

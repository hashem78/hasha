//
// Created by mythi on 29/07/22.
//

#include "NumericOperator.h"

namespace hasha {
    NumericOperator::Ptr NumericOperator::create(std::string op) {

        return std::make_unique<NumericOperator>(std::move(op));
    }

    nlohmann::json NumericOperator::to_json() const {

        return {
                {"token_type", "NumericOperator"},
                {"operator",   m_op}
        };
    }
} // hasha
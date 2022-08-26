//
// Created by mythi on 29/07/22.
//

#include "BooleanOperator.h"

namespace hasha {
    BooleanOperator::Ptr BooleanOperator::create(std::string op) {

        return std::make_unique<BooleanOperator>(std::move(op));
    }

    nlohmann::json BooleanOperator::to_json() const {

        return {
                {"token_type", "BooleanOperator"},
                {"operator",   m_op}
        };
    }
} // hasha
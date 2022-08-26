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
        using Ptr = std::unique_ptr<BooleanOperator>;

        static Ptr create(std::string op);

        [[nodiscard]]
        nlohmann::json to_json() const override;


    };

} // hasha

#endif //HASHA_BOOLEANOPERATOR_H

//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_NUMERICLITERAL_H
#define HASHA_NUMERICLITERAL_H

#include "Literal.h"

#include <memory>


namespace hasha {

    class NumericLiteral : public Literal {
        using Literal::Literal;
    public:
        using Ptr = std::unique_ptr<NumericLiteral>;

        static Ptr create(std::string literal);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };
}


#endif //HASHA_NUMERICLITERAL_H

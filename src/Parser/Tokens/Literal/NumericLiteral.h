//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_NUMERICLITERAL_H
#define HASHA_NUMERICLITERAL_H

#include "Literal.h"

#include <memory>


namespace hasha {

    class NumericLiteral : public Literal {
    public:
        using Literal::Literal;
        using Ptr = std::unique_ptr<NumericLiteral>;

        static Ptr create(std::string literal, const Span &span);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };
}


#endif //HASHA_NUMERICLITERAL_H

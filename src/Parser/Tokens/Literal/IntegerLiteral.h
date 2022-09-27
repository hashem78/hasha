//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_INTEGERLITERAL_H
#define HASHA_INTEGERLITERAL_H

#include "Literal.h"

namespace hasha {

    class IntegerLiteral : public Literal {
    public:
        using Literal::Literal;
        using Ptr = std::unique_ptr<IntegerLiteral>;

        static Ptr create(std::string literal, const Span &span, int scope_id);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };
}


#endif //HASHA_INTEGERLITERAL_H

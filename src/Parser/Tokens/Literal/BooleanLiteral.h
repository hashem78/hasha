//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_BOOLEANLITERAL_H
#define HASHA_BOOLEANLITERAL_H

#include "Literal.h"

namespace hasha {

    class BooleanLiteral : public Literal {
        using Literal::Literal;
    public:

        using Ptr = std::unique_ptr<BooleanLiteral>;
        static Ptr create(std::string literal);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };
}

#endif //HASHA_BOOLEANLITERAL_H

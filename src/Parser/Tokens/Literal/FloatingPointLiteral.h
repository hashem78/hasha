//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_FLOATINGPOINTLITERAL_H
#define HASHA_FLOATINGPOINTLITERAL_H

#include "Literal.h"

namespace hasha {

    class FloatingPointLiteral : public Literal {
    public:
        using Literal::Literal;
        using Ptr = std::unique_ptr<FloatingPointLiteral>;

        static Ptr create(std::string literal, const Span &span, int scope_id);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };
}


#endif //HASHA_FLOATINGPOINTLITERAL_H

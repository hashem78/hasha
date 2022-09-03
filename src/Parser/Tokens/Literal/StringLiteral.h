//
// Created by mythi on 29/07/22.
//

#ifndef HASHA_STRINGLITERAL_H
#define HASHA_STRINGLITERAL_H

#include "Literal.h"

namespace hasha {

    class StringLiteral : public Literal {
        using Literal::Literal;
    public:

        using Ptr = std::unique_ptr<StringLiteral>;

        static Ptr create(std::string literal, const Span &span);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };
}

#endif //HASHA_STRINGLITERAL_H

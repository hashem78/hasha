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

        using StringLiteralPtr = std::shared_ptr<StringLiteral>;

        static StringLiteralPtr create(std::string literal) {

            return std::make_shared<StringLiteral>(std::move(literal));
        }

        [[nodiscard]]
        nlohmann::json to_json() const override {

            return nlohmann::json{
                    {"token_type", "StringLiteral"},
                    {"literal",    m_literal}
            };
        }

        [[nodiscard]]
        std::string to_string() const override {

            return fmt::format("StringLiteral {}", m_literal);
        }
    };
}

#endif //HASHA_STRINGLITERAL_H

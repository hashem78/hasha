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

        using BooleanLiteralPtr = std::shared_ptr<BooleanLiteral>;
        static BooleanLiteralPtr create(std::string literal) {

            return std::make_shared<BooleanLiteral>(std::move(literal));
        }

        [[nodiscard]]
        nlohmann::json to_json() const override {

            return nlohmann::json{
                    {"token_type", "BooleanLiteral"},
                    {"literal",    m_literal}
            };
        }

        [[nodiscard]]
        std::string to_string() const override {

            return fmt::format("BooleanLiteral {}", m_literal);
        }
    };
}

#endif //HASHA_BOOLEANLITERAL_H

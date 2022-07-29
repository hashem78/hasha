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
        using NumericLiteralPtr = std::shared_ptr<NumericLiteral>;

        static NumericLiteralPtr create(std::string literal) {

            return std::make_shared<NumericLiteral>(std::move(literal));
        }

        [[nodiscard]]
        nlohmann::json to_json() const override {

            return nlohmann::json{
                    {"token_type", "NumericLiteral"},
                    {"literal",    m_literal}
            };
        }

        [[nodiscard]]
        std::string to_string() const override {

            return fmt::format("NumericLiteral {}", m_literal);
        }
    };
}


#endif //HASHA_NUMERICLITERAL_H

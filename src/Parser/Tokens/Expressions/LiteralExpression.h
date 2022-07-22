//
// Created by mythi on 22/07/22.
//

#ifndef HASHA_LITERALEXPRESSION_H
#define HASHA_LITERALEXPRESSION_H

#include "Expression.h"

namespace hasha {

    class LiteralExpression: public Expression {
        std::string m_literal;
        explicit LiteralExpression(std::string literal);
    public:
        using LiteralExpressionPtr = std::shared_ptr<LiteralExpression>;

        static LiteralExpressionPtr create(std::string literal);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;
    };

} // hasha

#endif //HASHA_LITERALEXPRESSION_H

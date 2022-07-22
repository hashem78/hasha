//
// Created by mythi on 22/07/22.
//

#ifndef HASHA_ARRAYEXPRESSION_H
#define HASHA_ARRAYEXPRESSION_H

#include "Expression.h"
#include "fmt/format.h"

namespace hasha {

    class ArrayExpression: public Expression {
        ExpressionListPtr expressions;
        explicit ArrayExpression(ExpressionListPtr expressions);
    public:
        using ArrayExpressionPtr = std::shared_ptr<ArrayExpression>;

        static ArrayExpressionPtr create(ExpressionListPtr expressions);

        ArrayExpression& add_expression(ExpressionPtr expression);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

    };

} // hasha

#endif //HASHA_ARRAYEXPRESSION_H

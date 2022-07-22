//
// Created by mythi on 22/07/22.
//

#ifndef HASHA_EXPRESSION_H
#define HASHA_EXPRESSION_H

#include "Token.h"

namespace hasha {

    class Expression : public Token {
    public:
        [[nodiscard]]
        nlohmann::json to_json() const override = 0;

        [[nodiscard]]
        std::string to_string() const override = 0;

    };

    using ExpressionPtr = std::shared_ptr<Expression>;
    using ExpressionList = std::deque<ExpressionPtr>;
    using ExpressionListPtr = std::shared_ptr<ExpressionList>;

    ExpressionListPtr create_expression_list();


} // hasha

#endif //HASHA_EXPRESSION_H

//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_EXPRESSION_H
#define HASHA_EXPRESSION_H

#include "Token.h"

namespace hasha {

    class Expression : public Token {
        TokenList expression;

    public:

        explicit Expression(TokenList expr, const Span &span);

        using Ptr = std::unique_ptr<Expression>;

        static Ptr create(TokenList expr, const Span &span);

        std::string evaluate();

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        bool empty() const;

    };

    using ExpressionList = std::vector<Expression::Ptr>;

    nlohmann::json expression_list_to_json(const ExpressionList &expression_list);
} // hasha

#endif //HASHA_EXPRESSION_H

//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_EXPRESSION_H
#define HASHA_EXPRESSION_H

#include "TokenBase.h"
#include "Token.h"

namespace hasha {

    class Expression : public TokenBase {
        TokenList m_expression;

    public:

        Expression(
                TokenList expr,
                Span span,
                int scope_id
        );

        [[nodiscard]]
        bool empty() const noexcept;

        [[nodiscard]]
        const TokenList &expression() const noexcept;
    };

    using BoxedExpression = Box<Expression>;
    using BoxedExpressionList = std::vector<BoxedExpression>;
} // hasha

#endif //HASHA_EXPRESSION_H
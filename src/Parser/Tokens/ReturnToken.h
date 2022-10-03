//
// Created by mythi on 04/10/22.
//

#ifndef HASHA_RETURNTOKEN_H
#define HASHA_RETURNTOKEN_H

#include "TokenBase.h"
#include "TokenForwards.h"
#include "Box.h"

namespace hasha {

    class ReturnToken : public TokenBase {
        Box<Expression> m_expression;
    public:

        explicit ReturnToken(
                Box<Expression> expression,
                Span span,
                int scope_id
        ) noexcept;

        [[nodiscard]]
        const Box<Expression> &expression() const noexcept;

    };

    using BoxedReturnToken = Box<ReturnToken>;

} // hasha

#endif //HASHA_RETURNTOKEN_H

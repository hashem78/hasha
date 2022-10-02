//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_IFSTATEMENT_H
#define HASHA_IFSTATEMENT_H

#include "TokenBase.h"
#include "TokenForwards.h"
#include "Box.h"

namespace hasha {

    class IfStatement : public TokenBase {

        Box<Expression> m_condition;
        Box<Block> m_block;
    public:

        IfStatement(
                Box<Expression> condition,
                Box<Block> block,
                const Span &span,
                int scope_id
        ) noexcept;

        [[nodiscard]]
        const Box<Expression> &condition() const noexcept;

        [[nodiscard]]
        const Box<Block> &block() const noexcept;
    };

    using BoxedIfStatement = Box<IfStatement>;

} // hasha

#endif //HASHA_IFSTATEMENT_H

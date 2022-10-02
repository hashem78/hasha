//
// Created by mythi on 02/10/22.
//

#include "ElifStatement.h"

namespace hasha {
    ElifStatement::ElifStatement(
            Box<Expression> condition,
            Box<Block> block,
            const Span &span,
            int scope_id
    ) noexcept:
            m_condition(std::move(condition)),
            m_block(std::move(block)),
            TokenBase(span, scope_id, "ElifStatement") {}

    const Expression &ElifStatement::condition() const noexcept {

        return *m_condition;
    }

    const Block &ElifStatement::block() const noexcept {

        return *m_block;
    }
} // hasha
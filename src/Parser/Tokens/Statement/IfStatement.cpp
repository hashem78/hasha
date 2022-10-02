//
// Created by mythi on 02/10/22.
//

#include "IfStatement.h"

namespace hasha {
    IfStatement::IfStatement(
            Box<Expression> condition,
            Box<Block> block,
            const Span &span,
            int scope_id
    ) noexcept:
            m_condition(std::move(condition)),
            m_block(std::move(block)),
            TokenBase(span, scope_id, "IfStatement"sv) {}

    const Expression &IfStatement::condition() const noexcept {

        return *m_condition;
    }

    const Block &IfStatement::block() const noexcept {

        return *m_block;
    }

} // hasha
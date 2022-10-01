//
// Created by mythi on 02/10/22.
//

#include "ElseStatement.h"

namespace hasha {
    ElseStatement::ElseStatement(
            Box<Block> block,
            Span span,
            int scope_id
    ) noexcept:
            m_block(std::move(block)),
            TokenBase(span, scope_id) {}

    const Block &ElseStatement::block() const noexcept {

        return *m_block;
    }
} // hasha
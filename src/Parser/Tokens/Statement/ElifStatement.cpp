//
// Created by mythi on 26/08/22.
//

#include "ElifStatement.h"

namespace hasha {

    ElifStatement::ElifStatement(
            Expression::Ptr condition,
            Block::Ptr block,
            const Span &span,
            int scope_id
    ) :
            m_condition(std::move(condition)),
            m_block(std::move(block)),
            Token(span, scope_id) {
    }

    ElifStatement::Ptr ElifStatement::create(
            Expression::Ptr condition,
            Block::Ptr block,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<ElifStatement>(
                std::move(condition),
                std::move(block),
                span,
                scope_id
        );
    }

    nlohmann::json ElifStatement::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "IfStatement";
        json["condition"] = m_condition->to_json();
        json["block"] = m_block->to_json();
        json["span"] = m_span.to_json();
        return json;
    }

    const Expression &ElifStatement::condition() const {

        return *m_condition;
    }

    const Block &ElifStatement::block() const {

        return *m_block;
    }



} // hasha
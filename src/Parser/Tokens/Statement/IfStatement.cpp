//
// Created by mythi on 26/08/22.
//

#include "IfStatement.h"



namespace hasha {
    IfStatement::IfStatement(
            Expression::Ptr condition,
            Block::Ptr block,
            const Span &span,
            int scope_id
    ) :
            condition(std::move(condition)),
            block(std::move(block)),
            Token(span,scope_id) {}

    const Expression& IfStatement::get_condition() const {

        return *condition;
    }

    const Block& IfStatement::get_block() const {

        return *block;
    }

    nlohmann::json IfStatement::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "IfStatement";
        json["condition"] = condition->to_json();
        json["block"] = block->to_json();
        json["span"] =m_span.to_json();
        return json;
    }

    IfStatement::Ptr IfStatement::create(
            Expression::Ptr condition,
            Block::Ptr block,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<IfStatement>(
                std::move(condition),
                std::move(block),
                span,
                scope_id
        );
    }
} // hasha
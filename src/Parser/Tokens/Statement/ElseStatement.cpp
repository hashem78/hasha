//
// Created by mythi on 26/08/22.
//

#include "ElseStatement.h"

namespace hasha {
    ElseStatement::ElseStatement(
            Block::Ptr block,
            const Span &span,
            int scope_id
    ) :
            IfStatement(nullptr, std::move(block), span, scope_id) {

    }

    ElseStatement::Ptr ElseStatement::create(Block::Ptr block, const Span &span, int scope_id) {

        return std::make_unique<ElseStatement>(std::move(block), span, scope_id);
    }

    nlohmann::json ElseStatement::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "ElseStatement";
        json["block"] = block->to_json();
        json["span"] = m_span.to_json();
        return json;
    }
} // hasha
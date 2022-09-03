//
// Created by mythi on 26/08/22.
//

#include "ElseStatement.h"

namespace hasha {
    ElseStatement::ElseStatement(Block::Ptr block, const Span &span) : IfStatement(nullptr, std::move(block), span) {

    }

    ElseStatement::Ptr ElseStatement::create(Block::Ptr block, const Span &span) {

        return std::make_unique<ElseStatement>(std::move(block), span);
    }

    nlohmann::json ElseStatement::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "ElseStatement";
        json["block"] = block->to_json();
        json["span"] =m_span.to_json();
        return json;
    }
} // hasha
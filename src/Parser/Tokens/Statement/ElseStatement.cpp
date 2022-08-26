//
// Created by mythi on 26/08/22.
//

#include "ElseStatement.h"

namespace hasha {
    ElseStatement::ElseStatement(Block::Ptr block): IfStatement(nullptr,std::move(block)) {

    }

    ElseStatement::Ptr ElseStatement::create(Block::Ptr block) {

        return std::make_unique<ElseStatement>(std::move(block));
    }

    nlohmann::json ElseStatement::to_json() const {
        auto json = nlohmann::json();
        json["token_type"] = "ElseStatement";
        json["block"] = block->to_json();
        return json;
    }
} // hasha
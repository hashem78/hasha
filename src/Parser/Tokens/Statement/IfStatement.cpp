//
// Created by mythi on 26/08/22.
//

#include "IfStatement.h"

#include <utility>

namespace hasha {
    IfStatement::IfStatement(TokenListPtr condition, Block::Ptr block) :
            condition(std::move(condition)),
            block(std::move(block)) {}

    const TokenList *IfStatement::get_condition() const {

        return condition.get();
    }

    const Block *IfStatement::get_block() const {

        return block.get();
    }

    nlohmann::json IfStatement::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "IfStatement";
        json["condition"] = token_list_to_json(condition.get());
        json["block"] = block->to_json();
        return json;
    }

    IfStatement::Ptr IfStatement::create(TokenListPtr condition, Block::Ptr block) {

        return std::make_unique<IfStatement>(std::move(condition), std::move(block));
    }
} // hasha
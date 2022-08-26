//
// Created by mythi on 21/07/22.
//

#include "Block.h"

namespace hasha {
    nlohmann::json Block::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Block";
        json["tokens"] = token_list_to_json(m_tokens.get());

        return json;
    }

    const TokenList &Block::get_tokens() const {

        return *m_tokens;
    }

    Block::Block(TokenListPtr m_tokens) : m_tokens(std::move(m_tokens)) {}

    Block::Ptr Block::create(TokenListPtr m_tokens) {

        return std::make_unique<Block>(std::move(m_tokens));
    }

} // hasha
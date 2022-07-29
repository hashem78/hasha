//
// Created by mythi on 21/07/22.
//

#include "Block.h"

namespace hasha {
    nlohmann::json Block::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Block";
        auto tokens_json = nlohmann::json::array();
        for (const auto &token: *m_tokens)
            tokens_json.push_back(token->to_json());
        json["m_tokens"] = tokens_json;

        return json;
    }

    std::string Block::to_string() const {

        std::string str = "- Block\n";
        for (const auto &token: *m_tokens) {
            str += fmt::format(" - {}\n", token->to_string());
        }
        return str;
    }

    const TokenList &Block::get_tokens() const {

        return *m_tokens;
    }

    Block::Block(TokenListPtr m_tokens) : m_tokens(std::move(m_tokens)) {}

    Block::BlockPtr Block::create(TokenListPtr m_tokens) {

        return std::make_unique<Block>(std::move(m_tokens));
    }

} // hasha
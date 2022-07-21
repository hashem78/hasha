//
// Created by mythi on 21/07/22.
//

#include "Block.h"

#include <memory>
#include <utility>

namespace hasha {
    nlohmann::json Block::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Block";
        auto tokens_json = nlohmann::json::array();
        for (const auto &token: *m_tokens)
            tokens_json.push_back(token->to_json());
        json["tokens"] = tokens_json;

        return json;
    }

    std::string Block::to_string() const {

        std::string str = "- Block\n";
        for (const auto &token: *m_tokens) {
            str += fmt::format("-> {}\n", token->to_string());
        }
        return str;
    }

    Block& Block::add(TokenPtr token) {

        m_tokens->push_back(std::move(token));
        return *this;
    }

    const TokenList &Block::get_tokens() const {

        return *m_tokens;
    }

    void Block::set_tokens(TokenListPtr tokens) {

        Block::m_tokens = std::move(tokens);
    }

    Block::Block(TokenListPtr m_tokens) : m_tokens(std::move(m_tokens)) {}

    Block::BlockPtr Block::create(TokenListPtr m_tokens) {
        return std::make_shared<Block>(std::move(m_tokens));
    }

} // hasha
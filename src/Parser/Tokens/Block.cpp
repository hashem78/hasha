//
// Created by mythi on 21/07/22.
//

#include "Block.h"


namespace hasha {
    nlohmann::json Block::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Block";
        json["tokens"] = token_list_to_json(m_tokens);
        json["span"] = m_span.to_json();

        return json;
    }

    const TokenList &Block::get_tokens() const {

        return m_tokens;
    }

    Block::Block(
            TokenList tokens,
            const Span &span,
            int scope_id
    ) : m_tokens(std::move(tokens)),
        Token(span, scope_id) {

    }

    Block::Ptr Block::create(TokenList tokens, const Span &span, int scope_id) {

        return std::make_unique<Block>(std::move(tokens), span, scope_id);
    }
} // hasha
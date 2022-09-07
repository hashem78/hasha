//
// Created by mythi on 21/07/22.
//

#include "Block.h"

#include <utility>
#include "GlobalScope.h"

namespace hasha {
    nlohmann::json Block::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "Block";
        json["tokens"] = token_list_to_json(m_tokens.get());
        json["span"] = m_span.to_json();

        return json;
    }

    TokenListPtr Block::get_tokens() const {

        return m_tokens;
    }

    Block::Block(TokenListPtr tokens, const Span &span) :
            m_tokens(std::move(tokens)),
            Token(span),
            m_scope(Scope::create(Token::id)) {}

    Block::Block(
            TokenListPtr tokens,
            const Span &span,
            Scope::Ptr scope
    ) : m_tokens(std::move(tokens)),
        Token(span),
        m_scope(std::move(scope)) {

    }


    Block::Ptr Block::create(TokenListPtr tokens, const Span &span) {

        return std::make_unique<Block>(std::move(tokens), span);
    }

    void Block::interpret(Scope::Ptr scope) {

        if (auto global_scope = std::dynamic_pointer_cast<GlobalScope>(scope)) {
            for (auto &token: *m_tokens) {
                token->interpret(global_scope);
            }
        } else {

            for (auto &token: *m_tokens) {
                token->interpret(m_scope);
            }
        }
    }

    Scope::Ptr Block::scope() {

        return m_scope;
    }


} // hasha
//
// Created by mythi on 21/07/22.
//

#include "Token.h"

namespace hasha {

    nlohmann::json token_list_to_json(const TokenList &tokens) {

        auto arr = nlohmann::json::array();
        for (const auto &token: tokens) {
            arr.push_back(token->to_json());
        }
        return arr;
    }

    std::string Token::to_string() const {

        std::stringstream str;
        str << std::setw(1) << to_json();
        return str.str();
    }

    Token::Token(const Span &span) :
            m_span(span),
            id(number_of_tokens++) {

    }


    int Token::number_of_tokens = 0;

    const Span &Token::span() const {

        return m_span;
    }

    ErrorOr<void> Token::interpret(Scope::Ptr scope) {
        return {};
    }


} // hasha
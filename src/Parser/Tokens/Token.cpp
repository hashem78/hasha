//
// Created by mythi on 21/07/22.
//

#include "Token.h"

namespace hasha {
    TokenListPtr create_token_list() {

        return std::make_shared<TokenList>();
    }

    void print_token_list(const TokenListPtr &tokens) {

        for (const auto &token: *tokens) {
            fmt::print("{}\n",token->to_string());
        }
    }
} // hasha
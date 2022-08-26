//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_TOKEN_H
#define HASHA_TOKEN_H

#include <memory>
#include <deque>

#include "nlohmann/json.hpp"
#include "fmt/core.h"

namespace hasha {

    class Token {
    public:
        Token() = default;

        [[nodiscard]]
        virtual nlohmann::json to_json() const = 0;

        [[nodiscard]]
        std::string to_string() const;

        virtual ~Token() = default;
    };

    using TokenPtr = std::unique_ptr<Token>;
    using TokenList = std::deque<TokenPtr>;
    using TokenListPtr = std::shared_ptr<TokenList>;

    TokenListPtr create_token_list();
    nlohmann::json token_list_to_json(const TokenList *tokens);

    void print_token_list(const TokenList* tokens);
} // hasha

#endif //HASHA_TOKEN_H

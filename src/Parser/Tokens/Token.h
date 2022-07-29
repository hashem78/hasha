//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_TOKEN_H
#define HASHA_TOKEN_H

#include <memory>
#include <deque>

#include "nlohmann/json.hpp"

namespace hasha {

    class Token {

    public:
        [[nodiscard]]
        virtual nlohmann::json to_json() const = 0;

        [[nodiscard]]
        virtual std::string to_string() const = 0;

        virtual ~Token() = default;
    };

    using TokenPtr = std::unique_ptr<Token>;
    using TokenList = std::deque<TokenPtr>;
    using TokenListPtr = std::shared_ptr<TokenList>;

    TokenListPtr create_token_list();
} // hasha

#endif //HASHA_TOKEN_H

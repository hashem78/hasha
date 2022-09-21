//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_TOKEN_H
#define HASHA_TOKEN_H

#include <memory>
#include <vector>
#include <utility>

#include "nlohmann/json.hpp"
#include "fmt/core.h"
#include "Span.h"
#include "ErrorOr.h"
#include "ScopeTree.h"

namespace hasha {

    class Token {
        static int number_of_tokens;
    protected:
        Span m_span;
        int id;
        int m_scope_id;

    public:
        explicit Token(const Span &span, int scope_id);

        [[nodiscard]]
        virtual nlohmann::json to_json() const = 0;

        [[nodiscard]]
        std::string to_string() const;

        [[nodiscard]]
        const Span &span() const;

        [[nodiscard]]
        int scope_id() const;

        virtual ~Token() = default;
    };

    using TokenPtr = std::unique_ptr<Token>;
    using TokenList = std::vector<TokenPtr>;

    nlohmann::json token_list_to_json(const TokenList &tokens);
} // hasha

#endif //HASHA_TOKEN_H

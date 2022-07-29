//
// Created by mythi on 30/07/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include <utility>

#include "Token.h"
#include "Identifier.h"
#include "fmt/format.h"

namespace hasha {

    class FunctionCall : public Token {
        Identifier::Ptr m_callee;
        TokenListPtr m_args;

        FunctionCall(Identifier::Ptr callee, TokenListPtr args);

    public:
        using Ptr = std::unique_ptr<FunctionCall>;

        static Ptr create(Identifier::Ptr callee, TokenListPtr args);

        [[nodiscard]]
        const Identifier::Ptr &get_callee() const;

        [[nodiscard]]
        const TokenListPtr &get_args() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

    };

} // hasha

#endif //HASHA_FUNCTIONCALL_H

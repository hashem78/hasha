//
// Created by mythi on 12/08/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include "Token.h"
#include "Tokens/Expression/Expression.h"

namespace hasha {

    class FunctionCall : public Token {
        std::string m_callee;
        ExpressionList m_arguments;

    public:

        FunctionCall(
                std::string callee,
                ExpressionList tokens,
                const Span &span,
                int scope_id
        );

        using Ptr = std::unique_ptr<FunctionCall>;

        static Ptr create(
                std::string callee,
                ExpressionList tokens,
                const Span& span,
                int scope_id
        );

        [[nodiscard]]
        int get_number_of_args() const noexcept;

        [[nodiscard]]
        std::string get_callee() const noexcept;

        [[nodiscard]]
        const ExpressionList& get_arguments() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_FUNCTIONCALL_H

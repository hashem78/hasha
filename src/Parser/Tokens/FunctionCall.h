//
// Created by mythi on 12/08/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include "Token.h"
#include "Expression.h"

namespace hasha {

    class FunctionCall : public Token {
        std::string m_callee;
        ExpressionListPtr m_arguments;

    public:

        FunctionCall(std::string callee,ExpressionListPtr tokens);

        using Ptr = std::unique_ptr<FunctionCall>;

        static Ptr create(std::string callee, ExpressionListPtr tokens);

        [[nodiscard]]
        int get_number_of_args() const noexcept;

        [[nodiscard]]
        std::string get_callee() const noexcept;

        [[nodiscard]]
        const ExpressionList* get_arguments() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_FUNCTIONCALL_H

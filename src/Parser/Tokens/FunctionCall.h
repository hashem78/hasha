//
// Created by mythi on 12/08/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include "Token.h"

namespace hasha {

    class FunctionCall : public Token {
        std::string m_callee;
        TokenListPtr m_arguments;

    public:

        FunctionCall(std::string callee,TokenListPtr tokens);

        using Ptr = std::unique_ptr<FunctionCall>;

        static Ptr create(std::string callee, TokenListPtr tokens);

        [[nodiscard]]
        int get_number_of_args() const noexcept;

        [[nodiscard]]
        std::string get_callee() const noexcept;

        [[nodiscard]]
        TokenListPtr get_arguments() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_FUNCTIONCALL_H

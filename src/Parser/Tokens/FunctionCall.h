//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include "TokenForwards.h"
#include "TokenBase.h"
#include "Box.h"

namespace hasha {

    class FunctionCall : public TokenBase {
        std::string m_callee;
        std::vector<Box<Expression>> m_arguments;

    public:

        FunctionCall(
                std::string callee,
                std::vector<Box<Expression>> tokens,
                const Span &span,
                int scope_id
        );


        [[nodiscard]]
        int get_number_of_args() const noexcept;

        [[nodiscard]]
        const std::string &get_callee() const noexcept;

        [[nodiscard]]
        const std::vector<Box<Expression>>& get_arguments() const noexcept;
    };
    using BoxedFunctionCall = Box<FunctionCall>;
} // hasha

#endif //HASHA_FUNCTIONCALL_H

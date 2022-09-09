//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_CONTEXT_H
#define HASHA_CONTEXT_H

#include <stack>

#include "fmt/format.h"
#include "nlohmann/json.hpp"

namespace hasha {

    struct Context {
        bool parsing_array;
        bool parsing_expression;
        bool parsing_args;
        bool parsing_array_type;
        bool parsing_value_type;
        bool parsing_return_expression;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(
                Context,
                parsing_array,
                parsing_expression,
                parsing_args, parsing_array_type,
                parsing_value_type,
                parsing_return_expression
        );

        Context &set_parsing_array(bool val) noexcept;

        Context &set_parsing_expression(bool val) noexcept;

        Context &set_parsing_args(bool val) noexcept;

        Context &set_parsing_array_type(bool val) noexcept;

        Context &set_parsing_value_type(bool val) noexcept;

        Context &set_parsing_return_expression(bool val) noexcept;


        void print();
    };

    using ContextStack = std::stack<Context>;
} // hasha

#endif //HASHA_CONTEXT_H

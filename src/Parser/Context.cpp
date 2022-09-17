//
// Created by mythi on 01/09/22.
//

#include <stack>

#include "Context.h"

namespace hasha {

    Context &Context::set_parsing_array(bool val) noexcept {

        parsing_array = val;
        return *this;
    }

    Context &Context::set_parsing_expression(bool val) noexcept {

        parsing_expression = val;
        return *this;
    }

    Context &Context::set_parsing_args(bool val) noexcept {

        parsing_args = val;
        return *this;
    }

    Context &Context::set_parsing_array_type(bool val) noexcept {

        parsing_array_type = val;
        return *this;
    }

    Context &Context::set_parsing_value_type(bool val) noexcept {

        parsing_value_type = val;
        return *this;
    }

    Context &Context::set_parsing_return_expression(bool val) noexcept {

        parsing_return_expression = val;
        return *this;
    }
}
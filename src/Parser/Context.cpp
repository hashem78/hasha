//
// Created by mythi on 01/09/22.
//

#include "Context.h"

namespace hasha {

    Context &Context::set_parsing_void_function(bool val) noexcept {
        parsing_void_function = val;
        return *this;
    }
}

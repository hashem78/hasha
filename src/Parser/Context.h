//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_CONTEXT_H
#define HASHA_CONTEXT_H

#include <stack>

namespace hasha {

    struct Context {

        bool parsing_void_function;

        Context &set_parsing_void_function(bool val) noexcept;

    };

    using ContextStack = std::stack<Context>;
} // hasha

#endif //HASHA_CONTEXT_H

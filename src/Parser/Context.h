//
// Created by mythi on 01/09/22.
//

#ifndef HASHA_CONTEXT_H
#define HASHA_CONTEXT_H

namespace hasha {

    struct Context {
        bool parsing_void_function;

        Context &set_parsing_void_function(bool val) noexcept;
    };
} // hasha

#endif //HASHA_CONTEXT_H

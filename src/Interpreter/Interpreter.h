//
// Created by mythi on 03/09/22.
//

#ifndef HASHA_INTERPRETER_H
#define HASHA_INTERPRETER_H

#include "Block.h"
#include "GlobalScope.h"

namespace hasha {

    class Interpreter {
        Block::Ptr global_block;
        GlobalScope::Ptr global_scope;

    public:
        explicit Interpreter(Block::Ptr block);
        ErrorOr<void> interpret();
    };

} // hasha

#endif //HASHA_INTERPRETER_H

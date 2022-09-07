//
// Created by mythi on 03/09/22.
//

#include "Interpreter.h"

namespace hasha {
    Interpreter::Interpreter(Block::Ptr block) : global_block(std::move(block)) {

    }

    void Interpreter::interpret() {

        global_block->interpret(global_scope);
    }
} // hasha
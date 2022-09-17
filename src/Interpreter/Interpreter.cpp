//
// Created by mythi on 03/09/22.
//

#include "Interpreter.h"

namespace hasha {
    Interpreter::Interpreter(Block::Ptr block) : global_block(std::move(block)) {

    }

    ErrorOr<void> Interpreter::interpret() {

        TRY(global_block->interpret());

        return {};
    }
} // hasha
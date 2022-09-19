//
// Created by mythi on 03/09/22.
//

#include "Interpreter.h"

namespace hasha {
    Interpreter::Interpreter(
            Block::Ptr block,
            ScopeTree::Ptr scope_tree
    ) :
            global_block(std::move(block)),
            scope_tree(std::move(scope_tree)) {
    }

    ErrorOr<void> Interpreter::interpret() {

        TRY(global_block->interpret(*scope_tree));

        return {};
    }
} // hasha
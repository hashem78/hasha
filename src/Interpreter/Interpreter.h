//
// Created by mythi on 03/09/22.
//

#ifndef HASHA_INTERPRETER_H
#define HASHA_INTERPRETER_H

#include "Block.h"
#include "ScopeTree.h"

namespace hasha {

    class Interpreter {
        Block::Ptr global_block;
        ScopeTree::Ptr scope_tree;
    public:
        explicit Interpreter(Block::Ptr block, ScopeTree::Ptr scope_tree);

        ErrorOr<void> interpret();
    };

} // hasha

#endif //HASHA_INTERPRETER_H

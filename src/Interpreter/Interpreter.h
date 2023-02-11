//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_INTERPRETER_H
#define HASHA_INTERPRETER_H

#include "Block.h"
#include "ErrorOr.h"
#include "ScopeTree.h"
#include "SymbolTableTree.h"

namespace hasha {

  class Interpreter {

    BoxedBlock global_block;
    ScopeTree::Ptr scope_tree;
    Scope::Ptr global_scope;
    SymbolTableTree::Ptr symbol_table_tree;

   public:
    explicit Interpreter(
      BoxedBlock block,
      ScopeTree::Ptr scope_tree,
      Scope::Ptr global_scope
    ) noexcept;

    ErrorOr<void> interpret();
    ErrorOr<void> first_pass();
    ErrorOr<void> second_pass();
  };

}// namespace hasha

#endif//HASHA_INTERPRETER_H

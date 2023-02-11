//
// Created by mythi on 03/10/22.
//

#ifndef HASHA_SYMBOLTABLETREE_H
#define HASHA_SYMBOLTABLETREE_H

#include "SymbolTable.h"

namespace hasha {

  class SymbolTableTree {
    SymbolTable::Ptr root;

   public:
    SymbolTableTree();

    SymbolTable::Ptr global_symbol_table();

    using Ptr = std::shared_ptr<SymbolTableTree>;

    static Ptr create();

    SymbolTable::Ptr create_table(SymbolTable::Ptr parent);

    [[nodiscard]] SymbolTable::Ptr get_by_id(uuid id) const;
  };

}// namespace hasha

#endif//HASHA_SYMBOLTABLETREE_H

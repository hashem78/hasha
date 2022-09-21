//
// Created by mythi on 20/09/22.
//

#ifndef HASHA_SYMBOLTREE_H
#define HASHA_SYMBOLTREE_H

#include <memory>
#include "SymbolTable.h"

namespace hasha {

    class SymbolTree {

        SymbolTable::Ptr root;


    public:

        SymbolTree();

        using Ptr = std::unique_ptr<SymbolTree>;

        static Ptr create();

        SymbolTable &create_table(int parent_id = 0);

        [[nodiscard]]
        SymbolTable *get_by_id(int id) const;
    };

} // hasha

#endif //HASHA_SYMBOLTREE_H

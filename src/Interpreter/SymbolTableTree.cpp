//
// Created by mythi on 20/09/22.
//

#include "SymbolTableTree.h"
#include <cassert>
#include <queue>

namespace hasha {

  SymbolTableTree::SymbolTableTree()
      : root(SymbolTable::create(0, nullptr)) {
  }

  SymbolTableTree::Ptr SymbolTableTree::create() {

    return std::make_shared<SymbolTableTree>();
  }

  SymbolTable::Ptr SymbolTableTree::create_table(SymbolTable::Ptr parent) {

    assert(root);

    if (parent->level == 0) {
      root->children.push_back(SymbolTable::create(1, root));
      return root->children.back();
    }

    root->children.push_back(SymbolTable::create(parent->level + 1, parent));
    return root->children.back();
    ;
  }

  SymbolTable::Ptr SymbolTableTree::get_by_id(uuid id) const {

    std::queue<SymbolTable::Ptr> trees;
    trees.push(root);
    while (!trees.empty()) {

      auto tree = trees.front();
      trees.pop();

      if (tree->id == id) {
        return tree;
      }

      for (auto &child: tree->children)
        trees.push(child);
    }
    return root;
  }

  SymbolTable::Ptr SymbolTableTree::global_symbol_table() {

    return root;
  }


}// namespace hasha
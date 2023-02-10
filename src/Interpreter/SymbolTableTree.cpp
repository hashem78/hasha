//
// Created by mythi on 20/09/22.
//

#include "SymbolTableTree.h"
#include <cassert>
#include <queue>

namespace hasha {

  SymbolTableTree::SymbolTableTree()
      : root(SymbolTable::create(nullptr)) {
  }

  SymbolTableTree::Ptr SymbolTableTree::create() {

    return std::make_shared<SymbolTableTree>();
  }

  SymbolTable::Ptr SymbolTableTree::create_table(const SymbolTable::Ptr &parent) {

    assert(root);

    if (parent->id == 0) {
      root->children.push_back(SymbolTable::create(root));
      return root->children.back();
    }

    root->children.push_back(SymbolTable::create(parent));
    return root->children.back();
    ;
  }

  SymbolTable::Ptr SymbolTableTree::get_by_id(int id) const {

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
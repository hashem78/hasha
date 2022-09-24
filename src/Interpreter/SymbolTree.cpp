//
// Created by mythi on 20/09/22.
//

#include <queue>
#include "SymbolTree.h"

namespace hasha::interpeter {

    SymbolTree::SymbolTree() : root(nullptr) {}

    SymbolTree::Ptr SymbolTree::create() {

        return std::make_unique<SymbolTree>();
    }

    SymbolTable &SymbolTree::create_table(int parent_id) {

        if (root == nullptr) {
            root = SymbolTable::create();
            return *root;
        }

        if (parent_id == 0) {
            root->children.push_back(SymbolTable::create(root.get()));
            return *root->children.back();
        }

        auto parent = get_by_id(parent_id);
        root->children.push_back(SymbolTable::create(parent));
        return *root->children.back();;
    }

    SymbolTable *SymbolTree::get_by_id(int id) const {

        std::queue<SymbolTable *> trees;
        trees.push(root.get());
        while (!trees.empty()) {

            auto tree = trees.front();
            trees.pop();

            if (tree->id == id) {
                return tree;
            }

            for (auto &child: tree->children)
                trees.push(child.get());
        }
        return root.get();
    }
} // hasha
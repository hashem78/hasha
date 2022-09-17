//
// Created by mythi on 17/09/22.
//

#include "ScopeTree.h"

namespace hasha {

    ScopeTree::ScopeTree() : root(nullptr) {}

    ScopeTree::Ptr ScopeTree::create() {

        return std::make_shared<ScopeTree>();
    }

    Scope &ScopeTree::create_scope(int parent_id) {

        if (root == nullptr) {
            root = Scope::create();
            return *root;
        }

        if (parent_id == 0) {
            root->children.push_back(Scope::create(root.get()));
            return *root->children.back();
        }

        auto parent = get_by_id(parent_id);
        root->children.push_back(Scope::create(parent));
        return *root->children.back();;
    }

    Scope *ScopeTree::get_by_id(int id) {

        std::queue<Scope *> scopes;
        scopes.push(root.get());
        while (!scopes.empty()) {

            auto scope = scopes.front();
            scopes.pop();

            if (scope->id == id) {
                return scope;
            }

            for (auto &child: scope->children)
                scopes.push(child.get());
        }
        return root.get();
    }

} // hasha
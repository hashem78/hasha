//
// Created by mythi on 17/09/22.
//

#include "ScopeTree.h"
#include "uuid.h"

namespace hasha {

  ScopeTree::ScopeTree()
      : root(nullptr) {
  }

  ScopeTree::Ptr ScopeTree::create() {

    return std::make_shared<ScopeTree>();
  }

  Scope::Ptr ScopeTree::create_scope(uuids::uuid parent_id, int parent_level) {

    if (root == nullptr) {
      root = Scope::create(nullptr, 0);
      return root;
    }

    if (parent_level == 0) {
      root->children.push_back(Scope::create(root, 1));
      return root->children.back();
    }

    auto parent = get_by_id(parent_id);
    root->children.push_back(Scope::create(parent, parent->level + 1));
    return root->children.back();
  }

  Scope::Ptr ScopeTree::get_by_id(uuids::uuid id) const {

    std::queue<Scope::Ptr> scopes;
    scopes.push(root);
    while (!scopes.empty()) {

      auto scope = scopes.front();
      scopes.pop();

      if (scope->id == id) {
        return scope;
      }

      for (auto &child: scope->children)
        scopes.push(child);
    }
    return root;
  }

  void ScopeTree::print() const {

    std::queue<Scope::Ptr> scopes;
    scopes.push(root);
    while (!scopes.empty()) {

      auto scope = scopes.front();
      scopes.pop();

      for (auto &child: scope->children)
        scopes.push(child);
    }
  }

}// namespace hasha
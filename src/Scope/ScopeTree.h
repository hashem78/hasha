//
// Created by mythi on 17/09/22.
//

#ifndef HASHA_SCOPETREE_H
#define HASHA_SCOPETREE_H

#include "Scope.h"

namespace hasha {

    class ScopeTree {
        Scope::Ptr root;


    public:
        ScopeTree();

        using Ptr = std::shared_ptr<ScopeTree>;

        static Ptr create();

        Scope &create_scope(int parent_id = 0);

        [[nodiscard]]
        Scope *get_by_id(int id) const;

    };

} // hasha

#endif //HASHA_SCOPETREE_H

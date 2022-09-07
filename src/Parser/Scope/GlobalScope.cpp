//
// Created by mythi on 06/09/22.
//

#include "GlobalScope.h"

namespace hasha {
    GlobalScope::GlobalScope(int owner_id) : Scope(owner_id) {

    }

    GlobalScope::Ptr GlobalScope::create(int owner_id) {

        return std::make_shared<GlobalScope>(owner_id);
    }
} // hasha
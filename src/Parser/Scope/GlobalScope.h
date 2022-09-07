//
// Created by mythi on 06/09/22.
//

#ifndef HASHA_GLOBALSCOPE_H
#define HASHA_GLOBALSCOPE_H

#include "Scope.h"

namespace hasha {

    struct GlobalScope : public Scope {
        explicit GlobalScope(int owner_id);

        using Ptr = std::shared_ptr<GlobalScope>;

        static Ptr create(int owner_id);
    };

} // hasha

#endif //HASHA_GLOBALSCOPE_H

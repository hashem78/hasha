//
// Created by mythi on 21/09/22.
//

#ifndef HASHA_HASHAVARIABLE_H
#define HASHA_HASHAVARIABLE_H

#include <string>
#include "Types/DefaultTypes.h"

namespace hasha {

    struct HashaVariable: std::variant<HashaNumber> {
        using std::variant<HashaNumber>::variant;
    };

} // hasha

#endif //HASHA_HASHAVARIABLE_H

//
// Created by mythi on 28/09/22.
//

#ifndef HASHA_DEFAULTTYPES_H
#define HASHA_DEFAULTTYPES_H


#include <variant>

namespace hasha {

    using HashaInteger = long long int;
    using HashaFloat = long double;

    using HashaNumber = std::variant<HashaInteger, HashaFloat>;
}

#endif //HASHA_DEFAULTTYPES_H

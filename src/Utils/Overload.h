//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_OVERLOAD_H
#define HASHA_OVERLOAD_H

namespace hasha {
    template<typename ...Ts>
    struct Overload : Ts ... {
        using Ts::operator()...;
    };

    template<typename ...Ts> Overload(Ts...) -> Overload<Ts...>;
}

#endif //HASHA_OVERLOAD_H

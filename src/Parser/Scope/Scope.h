//
// Created by mythi on 03/09/22.
//

#ifndef HASHA_SCOPE_H
#define HASHA_SCOPE_H

#include "fmt/core.h"

#include <string>
#include <vector>
#include <memory>

#include "Variable.h"

namespace hasha {

    struct Scope {
        int id;
        int owner_id;

        std::vector<Variable> variables;
        std::vector<std::string> functions;

        explicit Scope(int owner_id);

        using Ptr = std::shared_ptr<Scope>;

        static Ptr create(int owner_id);

        void print();

        virtual ~Scope() = default;

    private:
        static int id_;
    };

} // hasha

#endif //HASHA_SCOPE_H

//
// Created by mythi on 16/09/22.
//

#ifndef HASHA_SCOPE_H
#define HASHA_SCOPE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include "fmt/core.h"
#include "Box.h"
#include "TokenForwards.h"
namespace hasha {

    struct Scope : public std::enable_shared_from_this<Scope> {
        using Ptr = std::shared_ptr<Scope>;

        std::unordered_map<std::string, Box<Declaration>> declarations;
        std::unordered_map<std::string, Box<Parameter>> parameters;
        std::unordered_map<std::string, Box<Function>> functions;

        Ptr parent;
        int id;
        std::vector<Ptr> children;

        explicit Scope(Ptr parent);

        static Ptr create(Ptr parent);

        bool is_declaration_in_scope(const std::string &name);

        bool is_function_in_scope(const std::string &name);

        const Function *get_function(const std::string &name) const;

        const Declaration *get_declaration(const std::string &name) const;

        const Parameter *get_parameter(const std::string &name) const;

    private:
        static int _id;
    };

}
#endif //HASHA_SCOPE_H

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

namespace hasha {
    class Identifier;
    class Function;



    struct Scope {
        using Ptr = std::shared_ptr<Scope>;

        std::unordered_map<std::string, Identifier *> identifiers;
        std::unordered_map<std::string, Function *> functions;

        Scope *parent;
        int id;
        std::vector<Ptr> children;

        explicit Scope(Scope *parent = nullptr);

        static Ptr create(Scope *parent = nullptr);

        bool is_identifier_in_scope(const std::string &name);
        bool is_function_in_scope(const std::string &name);

    private:
        static int _id;
    };

}
#endif //HASHA_SCOPE_H

//
// Created by mythi on 06/09/22.
//

#ifndef HASHA_VARIABLE_H
#define HASHA_VARIABLE_H

#include <string>

namespace hasha {

    struct Variable {
        int id;
        std::string type;
        std::string name;
        std::string value;
        int scope_id;

        Variable(std::string type, std::string name, std::string value, int scope_id);

        bool operator==(const Variable &) const = default;

    private:
        static int id_gen;
    };


} // hasha

#endif //HASHA_VARIABLE_H

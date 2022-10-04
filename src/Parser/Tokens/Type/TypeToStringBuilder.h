//
// Created by mythi on 04/10/22.
//

#ifndef HASHA_TYPETOSTRINGBUILDER_H
#define HASHA_TYPETOSTRINGBUILDER_H

#include <string>
#include <vector>

#include "fmt/core.h"

#include "Type.h"
#include "NormalType.h"
#include "GenericType.h"

namespace hasha {
    struct TypeToStringBuilder {
        std::string operator()(const BoxedNormalType &obj) const noexcept {

            return obj->type();
        }

        std::string operator()(const BoxedGenericType &obj) const noexcept {

            std::string generic_str{};

            for (const auto &generic: obj->generics_list()) {
                generic_str += std::visit(TypeToStringBuilder{}, generic);
            }
            return fmt::format("{}<{}>", std::visit(TypeToStringBuilder{}, obj->type()), generic_str);

        }
    };
}

#endif //HASHA_TYPETOSTRINGBUILDER_H

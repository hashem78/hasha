//
// Created by mythi on 27/08/22.
//

#ifndef HASHA_ARRAYTYPE_H
#define HASHA_ARRAYTYPE_H

#include "Type.h"

namespace hasha {

    class ArrayType : public Type {
    public:
        using Type::Type;
        using Type::get_type;

        using Ptr = std::unique_ptr<ArrayType>;

        static Ptr create(std::string type, const Span &span);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ARRAYTYPE_H

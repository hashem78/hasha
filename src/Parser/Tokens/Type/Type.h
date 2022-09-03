//
// Created by mythi on 27/08/22.
//

#ifndef HASHA_TYPE_H
#define HASHA_TYPE_H

#include "Token.h"
#include "Identifier.h"

namespace hasha {

    class Type : public Token {
        Identifier name;
    public:
        explicit Type(Identifier name, const Span &span);

        using Ptr = std::unique_ptr<Type>;

        static Ptr create(Identifier name, const Span &span);

        [[nodiscard]]
        const Identifier &get_name() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_TYPE_H

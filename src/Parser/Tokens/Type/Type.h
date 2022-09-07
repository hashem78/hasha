//
// Created by mythi on 27/08/22.
//

#ifndef HASHA_TYPE_H
#define HASHA_TYPE_H

#include "Token.h"

namespace hasha {

    class Type : public Token {
        std::string type;
    public:
        explicit Type(std::string type, const Span &span);

        using Ptr = std::unique_ptr<Type>;

        static Ptr create(std::string type, const Span &span);

        [[nodiscard]]
        const std::string &get_type() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_TYPE_H

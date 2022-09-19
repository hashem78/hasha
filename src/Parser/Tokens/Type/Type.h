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
        explicit Type(std::string type, const Span &span, int scope_id);

        using Ptr = std::unique_ptr<Type>;

        static Ptr create(std::string type, const Span &span, int scope_id);

        [[nodiscard]]
        const std::string &get_type() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

    using TypeList = std::vector<Type::Ptr>;
    nlohmann::json type_list_to_json(const TypeList& type_list);

} // hasha

#endif //HASHA_TYPE_H

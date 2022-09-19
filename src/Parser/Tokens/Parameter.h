//
// Created by mythi on 25/07/22.
//

#ifndef HASHA_PARAMETER_H
#define HASHA_PARAMETER_H

#include "Token.h"
#include "Tokens/Type/Type.h"
#include "Identifier.h"

namespace hasha {

    class Parameter : public Token {
        Type::Ptr m_type;
        Identifier m_name;

    public:
        explicit Parameter(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                int scope_id
        ) noexcept;

        using Ptr = std::unique_ptr<Parameter>;

        static Ptr create(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        const Identifier &get_name() const noexcept;

        [[nodiscard]]
        const Type *get_type() const noexcept;

    };

} // hasha

#endif //HASHA_PARAMETER_H

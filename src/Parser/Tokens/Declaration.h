//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Token.h"
#include "fmt/format.h"
#include "Tokens/Assignment/Assignment.h"
#include "Type/Type.h"

namespace hasha {

    class Declaration : public Token {

    protected:

        Type::Ptr m_type;
        Identifier m_name;
        Assignment::Ptr m_assignment;

    public:

        Declaration(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                Assignment::Ptr asssignment = nullptr
        );

        using Ptr = std::unique_ptr<Declaration>;

        static Ptr create(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                Assignment::Ptr assignment = nullptr
        );

        [[nodiscard]]
        const Type *get_type() const;

        [[nodiscard]]
        Identifier get_name() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_DECLARATION_H

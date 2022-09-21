//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Token.h"
#include "fmt/format.h"
#include "Assignment.h"
#include "Tokens/Type/Type.h"
#include "Identifier.h"
#include "ErrorOr.h"

namespace hasha {

    class Declaration : public Token {

    protected:

        Type::Ptr m_type;
        Identifier m_name;
        Expression::Ptr m_assignment_expression;

    public:

        Declaration(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                int scope_id,
                Expression::Ptr assignment_expression = nullptr
        );

        using Ptr = std::unique_ptr<Declaration>;

        static Ptr create(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                int scope_id,
                Expression::Ptr assignment_expression = nullptr
        );

        [[nodiscard]]
        const Type &type() const;

        [[nodiscard]]
        const Identifier &name() const;

        [[nodiscard]]
        const Expression &assignment_expression() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_DECLARATION_H

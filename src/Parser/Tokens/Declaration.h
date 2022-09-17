//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Token.h"
#include "fmt/format.h"
#include "Assignment.h"
#include "Type.h"
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
                Expression::Ptr assignment_expression = nullptr
        );

        using Ptr = std::unique_ptr<Declaration>;

        static Ptr create(
                Type::Ptr type,
                Identifier name,
                const Span &span,
                Expression::Ptr assignment_expression = nullptr
        );

        [[nodiscard]]
        const Type *get_type() const;

        ErrorOr<void> interpret() override;

        [[nodiscard]]
        Identifier get_name() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_DECLARATION_H

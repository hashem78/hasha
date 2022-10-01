//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include <variant>
#include "TokenBase.h"
#include "Box.h"
#include "TokenForwards.h"


namespace hasha {

    class Declaration : public TokenBase {

    protected:

        std::variant<Box<NormalType>, Box<GenericType>> m_type;
        Box<Identifier> m_name;
        Box<Expression> m_assignment_expression;

    public:

        Declaration(
                std::variant<Box<NormalType>, Box<GenericType>> type,
                Box<Identifier> name,
                Box<Expression> assignment_expression,
                Span span,
                int scope_id
        ) noexcept;

        [[nodiscard]]
        const std::variant<Box<NormalType>, Box<GenericType>> &type() const noexcept;

        [[nodiscard]]
        const Identifier &name() const noexcept;

        [[nodiscard]]
        const Expression &assignment_expression() const noexcept;

    };

    using BoxedDeclaration = Box<Declaration>;
    using BoxedDeclarationList = std::vector<BoxedDeclaration>;
} // hasha

#endif //HASHA_DECLARATION_H
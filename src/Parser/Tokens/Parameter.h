//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_PARAMETER_H
#define HASHA_PARAMETER_H

#include <variant>
#include "TokenForwards.h"
#include "Box.h"
#include "TokenBase.h"

namespace hasha {

    class Parameter : public TokenBase {
        std::variant<Box<NormalType>, Box<GenericType>> m_type;
        Box<Identifier> m_name;

    public:
        Parameter(
                std::variant<Box<NormalType>, Box<GenericType>> type,
                Box<Identifier> name,
                Span span,
                int scope_id
        ) noexcept;

        [[nodiscard]]
        const Box<Identifier> &name() const noexcept;

        [[nodiscard]]
        const std::variant<Box<NormalType>, Box<GenericType>> &type() const noexcept;

    };

    using BoxedParameter = Box<Parameter>;
    using BoxedParameterList = std::vector<BoxedParameter>;


} // hasha

#endif //HASHA_PARAMETER_H

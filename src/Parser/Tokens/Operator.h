//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_OPERATOR_H
#define HASHA_OPERATOR_H

#include "TokenBase.h"
#include "Box.h"

namespace hasha {

    enum class OperatorType {
        Unary,
        Binary,
        Ternary
    };

    class Operator : public TokenBase {
    protected:
        OperatorType m_type;
        std::string m_op;

    public:
        Operator(
                OperatorType type,
                std::string op,
                Span span,
                int scope_id
        );

        [[nodiscard]]
        const std::string &operation() const noexcept;

        [[nodiscard]]
        OperatorType type() const noexcept;
    };
    using BoxedOperator = Box<Operator>;
} // hasha

#endif //HASHA_OPERATOR_H

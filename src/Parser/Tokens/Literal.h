//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_LITERAL_H
#define HASHA_LITERAL_H

#include "TokenBase.h"
#include "Box.h"

namespace hasha {
    enum class LiteralType {
        Integer,
        Float,
        String,
        Boolean
    };

    class Literal : public TokenBase {
    protected:

        LiteralType m_type;
        std::string m_literal;

    public:
        Literal(
                LiteralType type,
                std::string literal,
                Span span,
                int scope_id
        );

        [[nodiscard]]
        const std::string &literal() const noexcept;

        [[nodiscard]]
        LiteralType type() const;

    };
    using BoxedLiteral = Box<Literal>;
} // hasha

#endif //HASHA_LITERAL_H

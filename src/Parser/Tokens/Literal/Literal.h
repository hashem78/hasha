//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_LITERAL_H
#define HASHA_LITERAL_H

#include "Token.h"
#include "fmt/format.h"
#include "Type/Type.h"

namespace hasha {

    class Literal : public Token {
    protected:

        Type m_type;
        std::string m_literal;

    public:
        Literal(Type type, std::string literal, const Span &span, int scope_id);

        using Ptr = std::unique_ptr<Literal>;

        [[nodiscard]]
        const std::string &get_literal() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override = 0;

        [[nodiscard]]
        const Type &type() const;

    };


} // hasha

#endif //HASHA_LITERAL_H

//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_LITERAL_H
#define HASHA_LITERAL_H

#include <memory>

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Literal : public Token {
        using Ptr = std::shared_ptr<Literal>;
    protected:
        std::string m_literal;

    public:

        explicit Literal(std::string literal);

        [[nodiscard]]
        const std::string &get_literal() const noexcept;

    };


} // hasha

#endif //HASHA_LITERAL_H

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

    protected:
        std::string m_literal;

    public:
        explicit Literal(std::string literal) : m_literal(std::move(literal)) {

        }

        [[nodiscard]]
        const std::string &get_literal() const noexcept {

            return m_literal;
        }

        using LiteralPtr = std::shared_ptr<Literal>;
    };


} // hasha

#endif //HASHA_LITERAL_H

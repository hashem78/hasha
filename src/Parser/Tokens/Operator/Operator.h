//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_OPERATOR_H
#define HASHA_OPERATOR_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Operator : public Token {
    protected:
        std::string m_op;

    public:
        using Ptr = std::unique_ptr<Operator>;

        explicit Operator(std::string op) noexcept;

        [[nodiscard]]
        const std::string &get_op() const noexcept;
    };

} // hasha

#endif //HASHA_OPERATOR_H

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
        using OperatorPtr = std::shared_ptr<Operator>;

        explicit Operator(std::string op) noexcept: m_op(std::move(op)) {

        }

        [[nodiscard]]
        const std::string &get_op() const noexcept {

            return m_op;
        }
    };

} // hasha

#endif //HASHA_OPERATOR_H

//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_OPERATOR_H
#define HASHA_OPERATOR_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Operator : public Token {
        std::string m_op;

        explicit Operator(std::string op) noexcept;

    public:
        using OperatorPtr = std::shared_ptr<Operator>;

        static OperatorPtr create(std::string operatorx);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        const std::string &get_op() const noexcept;
    };

} // hasha

#endif //HASHA_OPERATOR_H

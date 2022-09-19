//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_OPERATOR_H
#define HASHA_OPERATOR_H

#include "Token.h"

namespace hasha {

    class Operator : public Token {
    protected:
        std::string m_op;

    public:
        Operator(std::string op, const Span &span, int scope_id) noexcept;

        using Ptr = std::unique_ptr<Operator>;

        static Ptr create(std::string op, const Span &span, int scope_id);

        [[nodiscard]]
        const std::string &get_op() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_OPERATOR_H

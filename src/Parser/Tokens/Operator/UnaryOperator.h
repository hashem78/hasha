//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_UNARYOPERATOR_H
#define HASHA_UNARYOPERATOR_H

#include "Token.h"

namespace hasha {

    class UnaryOperator : public Token {
    protected:
        std::string m_op;

    public:
        UnaryOperator(std::string op, const Span &span, int scope_id) noexcept;

        using Ptr = std::unique_ptr<UnaryOperator>;

        static Ptr create(std::string op, const Span &span, int scope_id);

        [[nodiscard]]
        const std::string &operation() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_UNARYOPERATOR_H

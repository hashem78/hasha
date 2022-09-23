//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_BINARYOPERATOR_H
#define HASHA_BINARYOPERATOR_H

#include "Token.h"

namespace hasha {

    class BinaryOperator : public Token {
    protected:
        std::string m_op;

    public:
        BinaryOperator(std::string op, const Span &span, int scope_id) noexcept;

        using Ptr = std::unique_ptr<BinaryOperator>;

        static Ptr create(std::string op, const Span &span, int scope_id);

        [[nodiscard]]
        const std::string &operation() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_BINARYOPERATOR_H

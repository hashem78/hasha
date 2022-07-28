//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_LITERAL_H
#define HASHA_LITERAL_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Literal: public Token {
        std::string m_literal;

        explicit Literal(std::string literal) noexcept;

    public:
        using LiteralPtr = std::shared_ptr<Literal>;

        static LiteralPtr create(std::string literal);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        const std::string &get_literal() const noexcept;

        void set_literal(const std::string &literal) noexcept;
    };

} // hasha

#endif //HASHA_LITERAL_H

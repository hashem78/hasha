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
        using Ptr = std::unique_ptr<Literal>;

        explicit Literal(std::string literal);

        [[nodiscard]]
        const std::string &get_literal() const noexcept;

        [[nodiscard]]
        nlohmann::json to_json() const override = 0;

    };


} // hasha

#endif //HASHA_LITERAL_H

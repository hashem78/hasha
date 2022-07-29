//
// Created by mythi on 24/07/22.
//

#ifndef HASHA_IDENTIFIER_H
#define HASHA_IDENTIFIER_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Identifier : public Token {

        std::string m_name;

        explicit Identifier(std::string name) noexcept;

    public:
        using IdentifierPtr = std::unique_ptr<Identifier>;
        using IdentifierRawPtr = Identifier*;

        static IdentifierPtr create(std::string name);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        const std::string &get_name() const noexcept;

        void set_name(const std::string &name) noexcept;

    };

} // hasha

#endif //HASHA_IDENTIFIER_H

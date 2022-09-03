//
// Created by mythi on 24/07/22.
//

#ifndef HASHA_IDENTIFIER_H
#define HASHA_IDENTIFIER_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Identifier : public Token {

        std::string m_identifier;


    public:
        explicit Identifier(std::string name, const Span &span) noexcept;

        using Ptr = std::unique_ptr<Identifier>;

        static Ptr create(std::string name, const Span &span);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        const std::string &get() const noexcept;

        void set(const std::string &name) noexcept;

    };

} // hasha

#endif //HASHA_IDENTIFIER_H

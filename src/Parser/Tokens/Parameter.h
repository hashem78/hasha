//
// Created by mythi on 25/07/22.
//

#ifndef HASHA_PARAMETER_H
#define HASHA_PARAMETER_H


#include <memory>

#include "Token.h"
#include "fmt/format.h"
#include "Identifier.h"

namespace hasha {

    class Parameter : public Token {
        Identifier m_name;
        Identifier m_type;

    public:
        explicit Parameter(Identifier name, Identifier type) noexcept;

        using Ptr = std::unique_ptr<Parameter>;

        static Ptr create(Identifier name, Identifier type);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        const Identifier &get_name() const noexcept;


        [[nodiscard]]
        const Identifier &get_type() const noexcept;

    };

} // hasha

#endif //HASHA_PARAMETER_H

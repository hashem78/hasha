//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_IDENTIFIER_H
#define HASHA_IDENTIFIER_H

#include "TokenBase.h"
#include "Box.h"

namespace hasha {

    class Identifier : public TokenBase {

        std::string m_identifier;

    public:
        explicit Identifier(
                std::string name,
                const Span &span,
                int scope_id
        ) noexcept;

        [[nodiscard]]
        const std::string &name() const noexcept;
    };

    using BoxedIdentifier = Box<Identifier>;

} // hasha

#endif //HASHA_IDENTIFIER_H

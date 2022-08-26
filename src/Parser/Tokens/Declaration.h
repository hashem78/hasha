//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Token.h"
#include "fmt/format.h"
#include "Assignment.h"
#include "Identifier.h"

namespace hasha {

    class Declaration : public Token {

    protected:

        Identifier m_type;
        Identifier m_name;
        bool m_isarray;
        Assignment::Ptr m_assignment;

    public:

        Declaration(
                Identifier type,
                Identifier name,
                Assignment::Ptr asssignment = nullptr,
                bool isarray = false
        );
        using Ptr = std::unique_ptr<Declaration>;

        static Ptr create(
                Identifier type,
                Identifier name,
                Assignment::Ptr assignment = nullptr,
                bool isarray = false
        );

        [[nodiscard]]
        Identifier get_type() const;

        [[nodiscard]]
        Identifier get_name() const;

        [[nodiscard]]
        TokenListPtr get_tokens() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_DECLARATION_H

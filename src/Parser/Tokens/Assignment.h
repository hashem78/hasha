//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_ASSIGNMENT_H
#define HASHA_ASSIGNMENT_H

#include "Token.h"
#include "fmt/format.h"
#include "Identifier.h"


namespace hasha {

    class Assignment : public Token {
    protected:

        bool m_isarray;

        [[nodiscard]]
        bool isarray() const;

    protected:
        Identifier m_name;
        TokenListPtr m_tokens;

    public:

        Assignment(Identifier name, TokenListPtr, bool isarray = false);

        using Ptr = std::unique_ptr<Assignment>;


        static Ptr create(Identifier name, TokenListPtr, bool isarray = false);

        [[nodiscard]]
        Identifier get_name() const;

        [[nodiscard]]
        TokenListPtr get_tokens() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

    };

} // hasha

#endif //HASHA_ASSIGNMENT_H

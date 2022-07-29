//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_ASSIGNMENT_H
#define HASHA_ASSIGNMENT_H

#include "Token.h"
#include "fmt/format.h"


namespace hasha {

    class Assignment : public Token {
    protected:

        bool m_isarray;
    public:
        bool isarray() const;

    protected:
        std::string m_name;
        TokenListPtr m_tokens;

        Assignment(std::string name, TokenListPtr, bool isarray = false);

    public:

        using AssignmentPtr = std::unique_ptr<Assignment>;

        static AssignmentPtr create(std::string name, TokenListPtr, bool isarray = false);

        [[nodiscard]]
        std::string get_name() const;

        [[nodiscard]]
        TokenListPtr get_tokens() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

    };

} // hasha

#endif //HASHA_ASSIGNMENT_H

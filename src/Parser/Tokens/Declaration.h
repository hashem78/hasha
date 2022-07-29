//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Token.h"
#include "fmt/format.h"
#include "Assignment.h"

namespace hasha {

    class Declaration : public Token {

    protected:

        std::string m_type;
        std::string m_name;
        bool m_isarray;
        Assignment::Ptr m_assignment;

        Declaration(
                std::string type,
                std::string name,
                Assignment::Ptr asssignment = nullptr,
                bool isarray = false
        );

    public:

        using Ptr = std::unique_ptr<Declaration>;

        static Ptr create(
                std::string type,
                std::string name,
                Assignment::Ptr assignment = nullptr,
                bool isarray = false
        );

        [[nodiscard]]
        std::string get_type() const;

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

#endif //HASHA_DECLARATION_H

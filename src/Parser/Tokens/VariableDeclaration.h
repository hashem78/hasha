//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_VARIABLEDECLARATION_H
#define HASHA_VARIABLEDECLARATION_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class VariableDeclaration : public Token {

    protected:

        std::string m_type;
        std::string m_name;
        bool m_isarray;
        TokenListPtr m_tokens;

        VariableDeclaration(std::string type, std::string name, TokenListPtr = nullptr, bool isarray = false);

    public:

        using VariableDeclarationPtr = std::shared_ptr<VariableDeclaration>;

        static VariableDeclarationPtr
        create(std::string type, std::string name, TokenListPtr = nullptr, bool isarray = false);


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

#endif //HASHA_VARIABLEDECLARATION_H

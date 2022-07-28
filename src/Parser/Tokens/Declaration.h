//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_DECLARATION_H
#define HASHA_DECLARATION_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class Declaration : public Token {

    protected:

        std::string m_type;
        std::string m_name;
        bool m_isarray;
        TokenListPtr m_tokens;

        Declaration(std::string type, std::string name, TokenListPtr = nullptr, bool isarray = false);

    public:

        using DeclarationPtr = std::shared_ptr<Declaration>;

        static DeclarationPtr
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

#endif //HASHA_DECLARATION_H

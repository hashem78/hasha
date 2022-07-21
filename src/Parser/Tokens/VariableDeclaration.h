//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_VARIABLEDECLARATION_H
#define HASHA_VARIABLEDECLARATION_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class VariableDeclaration : public Token {
        std::string type;
        std::string name;

        VariableDeclaration(std::string type, std::string name);

    public:

        using VariableDeclarationPtr = std::shared_ptr<VariableDeclaration>;

        static VariableDeclarationPtr create(std::string type, std::string name);


        [[nodiscard]]
        std::string get_type() const;

        VariableDeclaration &set_type(const std::string &type);

        [[nodiscard]]
        std::string get_name() const;

        VariableDeclaration &set_name(const std::string &var_name);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;
    };

} // hasha

#endif //HASHA_VARIABLEDECLARATION_H

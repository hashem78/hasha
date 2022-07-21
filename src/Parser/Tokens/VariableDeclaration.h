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
        std::string value;

        VariableDeclaration(std::string type, std::string name, std::string value = "");

    public:

        using VariableDeclarationPtr = std::shared_ptr<VariableDeclaration>;

        static VariableDeclarationPtr create(std::string type, std::string name, std::string value="");


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

        const std::string &get_value() const;

        void set_value(const std::string &value);
    };

} // hasha

#endif //HASHA_VARIABLEDECLARATION_H

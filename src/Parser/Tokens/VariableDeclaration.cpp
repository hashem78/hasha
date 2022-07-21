//
// Created by mythi on 21/07/22.
//

#include "VariableDeclaration.h"

#include <utility>


namespace hasha {
    std::string VariableDeclaration::get_type() const {

        return type;
    }

    VariableDeclaration &VariableDeclaration::set_type(const std::string &var_type) {

        VariableDeclaration::type = var_type;

        return *this;
    }

    std::string VariableDeclaration::get_name() const {

        return name;
    }

    VariableDeclaration &VariableDeclaration::set_name(const std::string &var_name) {

        VariableDeclaration::name = var_name;
        return *this;
    }

    nlohmann::json VariableDeclaration::to_json() const {

        auto json = nlohmann::json();

        json["type"] = type;
        json["name"] = name;
        json["token_type"] = "VariableDeclaration";

        return json;
    }

    std::string VariableDeclaration::to_string() const {

        return fmt::format("VariableDeclaration {} {}", type, name);
    }

    VariableDeclaration::VariableDeclaration(std::string type, std::string name) :
            type(std::move(type)),
            name(std::move(name)) {}

    VariableDeclaration::VariableDeclarationPtr VariableDeclaration::create(std::string type, std::string name) {

        return std::shared_ptr<VariableDeclaration>(new VariableDeclaration(std::move(type), std::move(name)));
    }
} // hasha
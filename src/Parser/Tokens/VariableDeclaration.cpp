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
        json["value"] = value;
        json["token_type"] = "VariableDeclaration";

        return json;
    }

    std::string VariableDeclaration::to_string() const {

        return fmt::format("VariableDeclaration {} {} {}", type, name, value);
    }

    VariableDeclaration::VariableDeclaration(std::string type, std::string name, std::string value) :
            type(std::move(type)),
            name(std::move(name)),
            value(std::move(value)) {}

    VariableDeclaration::VariableDeclarationPtr
    VariableDeclaration::create(std::string type, std::string name, std::string value) {

        return std::shared_ptr<VariableDeclaration>(
                new VariableDeclaration(std::move(type), std::move(name), std::move(value)));
    }

    const std::string &VariableDeclaration::get_value() const {

        return value;
    }

    void VariableDeclaration::set_value(const std::string &value) {

        VariableDeclaration::value = value;
    }
} // hasha
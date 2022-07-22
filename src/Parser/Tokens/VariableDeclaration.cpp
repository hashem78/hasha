//
// Created by mythi on 21/07/22.
//

#include "VariableDeclaration.h"

#include <utility>


namespace hasha {
    std::string VariableDeclaration::get_type() const {

        return m_type;
    }

    VariableDeclaration &VariableDeclaration::set_type(const std::string &var_type) {

        VariableDeclaration::m_type = var_type;

        return *this;
    }

    std::string VariableDeclaration::get_name() const {

        return m_name;
    }

    VariableDeclaration &VariableDeclaration::set_name(const std::string &var_name) {

        VariableDeclaration::m_name = var_name;
        return *this;
    }

    nlohmann::json VariableDeclaration::to_json() const {

        auto json = nlohmann::json();

        json["type"] = m_type;
        json["name"] = m_name;
        json["expression"] = m_expression->to_json();
        json["token_type"] = "VariableDeclaration";

        return json;
    }

    std::string VariableDeclaration::to_string() const {

        return fmt::format("VariableDeclaration {} {} Expression: {}", m_type, m_name, m_expression->to_string());
    }

    VariableDeclaration::VariableDeclaration(std::string type, std::string name, ExpressionPtr expression) :
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_expression(std::move(expression)) {}

    VariableDeclaration::VariableDeclarationPtr
    VariableDeclaration::create(std::string type, std::string name, ExpressionPtr expression) {

        return std::shared_ptr<VariableDeclaration>(
                new VariableDeclaration(std::move(type), std::move(name), std::move(expression)));
    }

    ExpressionPtr VariableDeclaration::get_expression() const {

        return m_expression;
    }

    VariableDeclaration &VariableDeclaration::set_expression(const ExpressionPtr &expression) {

        VariableDeclaration::m_expression = expression;
        return *this;
    }
} // hasha
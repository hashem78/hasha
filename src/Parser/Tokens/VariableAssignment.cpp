//
// Created by mythi on 21/07/22.
//

#include "VariableAssignment.h"


namespace hasha {
    VariableAssignment::VariableAssignment(std::string variable_name, ExpressionPtr expression)
            : m_variable_name(std::move(variable_name)),
              m_expression(std::move(expression)) {}

    nlohmann::json VariableAssignment::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "VariableAssignment";
        json["variable_name"] = m_variable_name;
        json["expression"] = m_expression->to_json();
        return json;
    }

    std::string VariableAssignment::to_string() const {

        return fmt::format("VariableAssignment {} {}", m_variable_name, m_expression->to_string());
    }

    const std::string &VariableAssignment::get_variable_name() const {

        return m_variable_name;
    }

    void VariableAssignment::set_variable_name(const std::string &variable_name) {

        VariableAssignment::m_variable_name = variable_name;
    }

    ExpressionPtr VariableAssignment::get_expression() const {

        return m_expression;
    }

    void VariableAssignment::set_expression(ExpressionPtr expression) {

        VariableAssignment::m_expression = std::move(expression);
    }

    VariableAssignment::VariableAssignmentPtr
    VariableAssignment::create(std::string variable_name, ExpressionPtr expression) {

        return std::shared_ptr<VariableAssignment>(
                new VariableAssignment(std::move(variable_name), std::move(expression)));

    }
} // hasha
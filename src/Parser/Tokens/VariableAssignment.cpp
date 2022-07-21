//
// Created by mythi on 21/07/22.
//

#include "VariableAssignment.h"


namespace hasha {
    VariableAssignment::VariableAssignment(std::string variable_name, std::string value)
            : m_variable_name(std::move(variable_name)),
              m_value(std::move(value)) {}

    nlohmann::json VariableAssignment::to_json() const {

        auto json = nlohmann::json();
        json["token_type"] = "VariableAssignment";
        json["variable_name"] = m_variable_name;
        json["value"] = m_value;
        return json;
    }

    std::string VariableAssignment::to_string() const {

        return fmt::format("VariableAssignment {} {}", m_variable_name, m_value);
    }

    const std::string &VariableAssignment::get_variable_name() const {

        return m_variable_name;
    }

    void VariableAssignment::set_variable_name(const std::string &variable_name) {

        VariableAssignment::m_variable_name = variable_name;
    }

    const std::string &VariableAssignment::get_value() const {

        return m_value;
    }

    void VariableAssignment::set_value(const std::string &value) {

        VariableAssignment::m_value = value;
    }

    VariableAssignment::VariableAssignmentPtr VariableAssignment::create(std::string variable_name, std::string value) {

        return std::shared_ptr<VariableAssignment>(new VariableAssignment(std::move(variable_name), std::move(value)));

    }
} // hasha
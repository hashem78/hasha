//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_VARIABLEASSIGNMENT_H
#define HASHA_VARIABLEASSIGNMENT_H

#include <string>
#include <memory>
#include <utility>

#include "Token.h"

#include "fmt/format.h"


namespace hasha {

    class VariableAssignment : public Token {
        VariableAssignment(std::string variable_name, std::string value);

    public:
        using VariableAssignmentPtr = std::shared_ptr<VariableAssignment>;

        static VariableAssignmentPtr create(std::string variable_name, std::string value);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        const std::string &get_variable_name() const;

        void set_variable_name(const std::string &variable_name);

        [[nodiscard]]
        const std::string &get_value() const;

        void set_value(const std::string &value);

    private:
        std::string m_variable_name;
        std::string m_value;

    };

} // hasha

#endif //HASHA_VARIABLEASSIGNMENT_H

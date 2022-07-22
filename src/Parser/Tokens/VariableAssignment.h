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
#include "Expressions/Expression.h"


namespace hasha {

    class VariableAssignment : public Token {
        std::string m_variable_name;
        ExpressionPtr m_expression;

        VariableAssignment(std::string variable_name, ExpressionPtr expression);

    public:
        using VariableAssignmentPtr = std::shared_ptr<VariableAssignment>;

        static VariableAssignmentPtr create(std::string variable_name, ExpressionPtr expression);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        const std::string &get_variable_name() const;

        void set_variable_name(const std::string &variable_name);

        [[nodiscard]]
        ExpressionPtr get_expression() const;

        void set_expression(ExpressionPtr expression);


    };

} // hasha

#endif //HASHA_VARIABLEASSIGNMENT_H

//
// Created by mythi on 22/07/22.
//

#include "ArrayDeclaration.h"

#include <utility>

namespace hasha {
    nlohmann::json ArrayDeclaration::to_json() const {


        auto json = nlohmann::json();

        json["type"] = m_type;
        json["name"] = m_name;
        json["expression"] = m_expression->to_json();
        json["token_type"] = "ArrayDeclaration";

        return json;
    }

    std::string ArrayDeclaration::to_string() const {

        if (m_expression != nullptr) {

            return fmt::format("ArrayDeclaration {} {} Expression: {}", m_type, m_name, m_expression->to_string());
        }


        return fmt::format("ArrayDeclaration {} {}", m_type, m_name);
    }

    ArrayDeclaration::ArrayDeclaration(
            std::string type, std::string name,
            ArrayExpression::ArrayExpressionPtr array_expression) :
            VariableDeclaration(std::move(type), std::move(name), std::move(array_expression)) {

    }

    ArrayDeclaration::ArrayDeclarationPtr
    ArrayDeclaration::create(std::string type, std::string name, ArrayExpression::ArrayExpressionPtr array_expression) {

        return std::shared_ptr<ArrayDeclaration>(
                new ArrayDeclaration(std::move(type),
                                     std::move(name),
                                     std::move(array_expression)));
    }

} // hasha
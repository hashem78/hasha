//
// Created by mythi on 22/07/22.
//

#ifndef HASHA_ARRAYDECLARATION_H
#define HASHA_ARRAYDECLARATION_H

#include "VariableDeclaration.h"
#include "Expressions/ArrayExpression.h"

namespace hasha {

    class ArrayDeclaration: public VariableDeclaration {

        ArrayDeclaration(std::string type, std::string name, ArrayExpression::ArrayExpressionPtr array_expression = nullptr);
    public:

        using ArrayDeclarationPtr = std::shared_ptr<ArrayDeclaration>;

        static ArrayDeclarationPtr create(std::string type, std::string name, ArrayExpression::ArrayExpressionPtr array_expression = nullptr);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

    };

} // hasha

#endif //HASHA_ARRAYDECLARATION_H

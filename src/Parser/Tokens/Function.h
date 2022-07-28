//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_FUNCTION_H
#define HASHA_FUNCTION_H

#include "Token.h"
#include "Block.h"
#include "Parameter.h"
#include "Identifier.h"

namespace hasha {


    class Function : public Token {
        Parameter::ParameterListPtr m_parameters;
        Block::BlockPtr m_block;
        Identifier::IdentifierPtr m_name;

        Function(Parameter::ParameterListPtr parameters, Block::BlockPtr block, Identifier::IdentifierPtr name);

    public:
        using FunctionPtr = std::shared_ptr<Function>;

        static FunctionPtr
        create(Parameter::ParameterListPtr parameters, Block::BlockPtr block, Identifier::IdentifierPtr name);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        Parameter::ParameterListPtr get_parameters() const;

        [[nodiscard]]
        const Block &get_block() const;

        [[nodiscard]]
        Identifier::IdentifierPtr get_name() const;


    };

} // hasha

#endif //HASHA_FUNCTION_H

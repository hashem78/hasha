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

        Function &add_param(Parameter::ParameterPtr param);

        Function &add_to_block(TokenPtr token);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        Parameter::ParameterListPtr get_parameters() const;

        void set_parameters(Parameter::ParameterListPtr parameters);

        [[nodiscard]]
        const Block &get_block() const;

        void set_block(Block::BlockPtr block);

        [[nodiscard]]
        Identifier::IdentifierPtr get_name() const;

        void set_name(Identifier::IdentifierPtr name);


    };

} // hasha

#endif //HASHA_FUNCTION_H

//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_FUNCTION_H
#define HASHA_FUNCTION_H

#include "Token.h"
#include "Block.h"
#include "Declarations/VariableDeclaration.h"

namespace hasha {

    using ParameterList = std::deque<VariableDeclaration::VariableDeclarationPtr>;
    using ParameterListPtr = std::shared_ptr<ParameterList>;

    ParameterListPtr create_parameter_list();

    nlohmann::json parameter_list_to_json(const ParameterList &parameter_list);

    class Function : public Token {
        ParameterListPtr m_parameters;
        Block::BlockPtr m_block;
        std::string m_name;

        Function(ParameterListPtr parameters, Block::BlockPtr block, std::string name);

    public:
        using FunctionPtr = std::shared_ptr<Function>;

        static FunctionPtr create(ParameterListPtr parameters, Block::BlockPtr block, std::string m_name);

        Function &add_param(VariableDeclaration::VariableDeclarationPtr param);

        Function &add_to_block(TokenPtr token);

        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        ParameterListPtr get_parameters() const;

        void set_parameters(ParameterListPtr parameters);

        [[nodiscard]]
        const Block &get_block() const;

        void set_block(Block::BlockPtr block);

        [[nodiscard]]
        const std::string &get_name() const;

        void set_name(const std::string &name);


    };

} // hasha

#endif //HASHA_FUNCTION_H

//
// Created by mythi on 21/07/22.
//

#include "Function.h"

namespace hasha {
    nlohmann::json Function::to_json() const {

        auto json = nlohmann::json();

        json["token_type"] = "Function";
        json["name"] = m_name.get();
        json["return_type"] = m_return_type->to_json();
        json["parameters"] = token_list_to_json(m_parameters.get());
        json["block"] = m_block->to_json();
        json["return_expression"] = token_list_to_json(m_return_expression.get());

        return json;
    }

    TokenListPtr Function::get_parameters() const {

        return m_parameters;
    }

    const class Block *Function::get_block() const {

        return m_block.get();
    }


    Function::Function(
            TokenListPtr parameters,
            Block::Ptr block,
            Identifier name,
            Type::Ptr return_type,
            TokenListPtr return_expression
    )
            : m_parameters(std::move(parameters)),
              m_block(std::move(block)),
              m_return_type(std::move(return_type)),
              m_name(std::move(name)),
              m_return_expression(std::move(return_expression)) {
    }

    Function::Ptr Function::create(
            TokenListPtr parameters,
            Block::Ptr block,
            Identifier name,
            Type::Ptr return_type,
            TokenListPtr return_expression
    ) {

        return std::make_unique<Function>(

                std::move(parameters),
                std::move(block),
                std::move(name),
                std::move(return_type),
                std::move(return_expression)

        );
    }

    Identifier Function::get_name() const {

        return m_name;
    }

    const Type* Function::get_return_type() const {

        return m_return_type.get();
    }


} // hasha
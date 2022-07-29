//
// Created by mythi on 21/07/22.
//

#include "Function.h"

namespace hasha {
    nlohmann::json Function::to_json() const {

        auto json = nlohmann::json();

        json["token_type"] = "Function";
        json["name"] = m_name->get_name();
        json["return_type"] = m_return_type->get_name();
        json["parameters"] = Parameter::list_to_json(m_parameters);
        json["block"] = m_block->to_json();
        json["return_expression"] = nlohmann::json::array();
        for (const auto &token: *m_return_expression)
            json["return_expression"].push_back(token->to_json());

        return json;
    }

    std::string Function::to_string() const {

        std::string str = fmt::format("-> Function {} {} \n - Parameters\n", m_name->get_name(),
                                      m_return_type->get_name());

        for (const auto &param: *m_parameters) {
            str += fmt::format("  -> {}\n", param->to_string());
        }
        str += m_block->to_string();
        std::string return_str;
        for (const auto &token: *m_return_expression) {
            return_str += token->to_string();
        }
        str += fmt::format("- Returns {}\n", return_str);

        return str;
    }

    Parameter::ParameterListPtr Function::get_parameters() const {

        return m_parameters;
    }

    const Block &Function::get_block() const {

        return *m_block;
    }


    Identifier::IdentifierPtr Function::get_name() const {

        return m_name;
    }


    Function::Function(
            Parameter::ParameterListPtr parameters,
            Block::BlockPtr block,
            Identifier::IdentifierPtr return_type,
            Identifier::IdentifierPtr name,
            TokenListPtr return_expression
    )
            : m_parameters(std::move(parameters)),
              m_block(std::move(block)),
              m_return_type(std::move(return_type)),
              m_name(std::move(name)),
              m_return_expression(std::move(return_expression)) {
    }

    Function::FunctionPtr Function::create(
            Parameter::ParameterListPtr parameters,
            Block::BlockPtr block,
            Identifier::IdentifierPtr return_type,
            Identifier::IdentifierPtr name,
            TokenListPtr return_expression
    ) {

        return std::shared_ptr<Function>(
                new Function(
                        std::move(parameters),
                        std::move(block),
                        std::move(name),
                        std::move(return_type),
                        std::move(return_expression)
                )
        );
    }

    Identifier::IdentifierPtr Function::get_return_type() const {

        return m_return_type;
    }


} // hasha
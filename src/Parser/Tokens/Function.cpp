//
// Created by mythi on 21/07/22.
//

#include "Function.h"

#include <utility>

namespace hasha {
    nlohmann::json Function::to_json() const {

        auto json = nlohmann::json();

        json["token_type"] = "Function";
        json["parameters"] = parameter_list_to_json(*m_parameters);
        json["block"] = m_block->to_json();

        return json;
    }

    std::string Function::to_string() const {

        std::string str = fmt::format("Function {}\n- Parameters\n", m_name);
        for (const auto &param: *m_parameters) {
            str += fmt::format("-> {}\n", param->to_string());
        }
        str += m_block->to_string();


        return str;
    }

    Function &Function::add_param(VariableDeclaration::VariableDeclarationPtr param) {

        m_parameters->push_back(std::move(param));
        return *this;
    }

    Function &Function::add_to_block(TokenPtr token) {

        m_block->add(std::move(token));
        return *this;
    }

    ParameterListPtr Function::get_parameters() const {

        return m_parameters;
    }

    void Function::set_parameters(ParameterListPtr parameters) {

        Function::m_parameters = std::move(parameters);
    }

    const Block &Function::get_block() const {

        return *m_block;
    }

    void Function::set_block(Block::BlockPtr block) {

        Function::m_block = std::move(block);
    }

    const std::string &Function::get_name() const {

        return m_name;
    }

    void Function::set_name(const std::string &name) {

        Function::m_name = name;
    }

    Function::Function(ParameterListPtr parameters, Block::BlockPtr block, std::string name)
            : m_parameters(std::move(parameters)),
              m_block(std::move(block)),
              m_name(std::move(name)) {
    }

    Function::FunctionPtr Function::create(ParameterListPtr parameters, Block::BlockPtr block, std::string name) {

        return std::shared_ptr<Function>(new Function(std::move(parameters), std::move(block), std::move(name)));
    }

    nlohmann::json parameter_list_to_json(const ParameterList &parameter_list) {

        auto json = nlohmann::json::array();
        for (const auto &param: parameter_list)
            json.push_back(param->to_json());

        return json;
    }

    ParameterListPtr create_parameter_list() {
        return std::make_shared<ParameterList>();

    }
} // hasha
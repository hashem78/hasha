//
// Created by mythi on 21/07/22.
//

#include "VariableDeclaration.h"

namespace hasha {
    std::string VariableDeclaration::get_type() const {

        return m_type;
    }

    std::string VariableDeclaration::get_name() const {

        return m_name;
    }


    nlohmann::json VariableDeclaration::to_json() const {

        auto json = nlohmann::json();

        json["type"] = m_type;
        json["name"] = m_name;

        if (m_isarray) {
            json["token_type"] = "ArrayDeclaration";
        } else {
            json["token_type"] = "VariableDeclaration";
        }

        if (m_tokens != nullptr) {

            json["tokens"] = nlohmann::json::array();
            for (const auto &token: *m_tokens) {
                json["tokens"].push_back(token->to_json());
            }
        }

        return json;
    }

    std::string VariableDeclaration::to_string() const {

        if (m_tokens != nullptr) {
            std::string str;
            if (m_isarray) {
                str = fmt::format("ArrayDeclaration {}[] {}\n - Assigned to: [ ", m_type, m_name);
            } else {
                str = fmt::format("VariableDeclaration {} {}\n - Assigned to: ", m_type, m_name);
            }
            for (const auto &token: *m_tokens) {
                str += fmt::format("{} ", token->to_string());
            }
            if (m_isarray) {
                str += "]";
            }
            return str;
        }

        if(m_isarray){
            return fmt::format("ArrayDeclaration {} {}", m_type, m_name);
        }

        return fmt::format("VariableDeclaration {} {}", m_type, m_name);

    }

    VariableDeclaration::VariableDeclaration(std::string type, std::string name, TokenListPtr tokens, bool isarray) :
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_tokens(std::move(tokens)),
            m_isarray(isarray) {}

    VariableDeclaration::VariableDeclarationPtr
    VariableDeclaration::create(std::string type, std::string name, TokenListPtr tokens, bool isarray) {

        return std::shared_ptr<VariableDeclaration>(
                new VariableDeclaration(std::move(type), std::move(name), std::move(tokens), isarray));
    }

    TokenListPtr VariableDeclaration::get_tokens() const {

        return m_tokens;
    }


} // hasha
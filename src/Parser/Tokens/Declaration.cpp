//
// Created by mythi on 21/07/22.
//

#include "Declaration.h"

namespace hasha {
    std::string Declaration::get_type() const {

        return m_type;
    }

    std::string Declaration::get_name() const {

        return m_name;
    }


    nlohmann::json Declaration::to_json() const {

        auto json = nlohmann::json();

        json["type"] = m_type;
        json["name"] = m_name;

        if (m_isarray) {
            json["token_type"] = "ArrayDeclaration";
        } else {
            json["token_type"] = "Declaration";
        }

        if (m_tokens != nullptr) {

            json["tokens"] = nlohmann::json::array();
            for (const auto &token: *m_tokens) {
                json["tokens"].push_back(token->to_json());
            }
        }

        return json;
    }

    std::string Declaration::to_string() const {

        if (m_tokens != nullptr) {
            std::string str;
            if (m_isarray) {
                str = fmt::format("ArrayDeclaration {}[] {}\n - Assigned to: [ ", m_type, m_name);
            } else {
                str = fmt::format("Declaration {} {}\n - Assigned to: ", m_type, m_name);
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

        return fmt::format("Declaration {} {}", m_type, m_name);

    }

    Declaration::Declaration(std::string type, std::string name, TokenListPtr tokens, bool isarray) :
            m_type(std::move(type)),
            m_name(std::move(name)),
            m_tokens(std::move(tokens)),
            m_isarray(isarray) {}

    Declaration::DeclarationPtr
    Declaration::create(std::string type, std::string name, TokenListPtr tokens, bool isarray) {

        return std::shared_ptr<Declaration>(
                new Declaration(std::move(type), std::move(name), std::move(tokens), isarray));
    }

    TokenListPtr Declaration::get_tokens() const {

        return m_tokens;
    }


} // hasha
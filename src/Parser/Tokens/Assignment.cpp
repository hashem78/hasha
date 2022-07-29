//
// Created by mythi on 28/07/22.
//

#include "Assignment.h"

namespace hasha {


    std::string Assignment::get_name() const {

        return m_name;
    }


    nlohmann::json Assignment::to_json() const {

        auto json = nlohmann::json();

        json["name"] = m_name;

        if (m_isarray) {
            json["token_type"] = "ArrayAssignment";
        } else {
            json["token_type"] = "Assignment";
        }


        json["tokens"] = nlohmann::json::array();
        for (const auto &token: *m_tokens) {
            json["tokens"].push_back(token->to_json());
        }


        return json;
    }

    std::string Assignment::to_string() const {

        std::string str;
        for (const auto &token: *m_tokens) {
            str += fmt::format("{} ", token->to_string());
        }
        if (m_isarray) {

            return fmt::format("ArrayAssignment {}\n     - [ {}]", m_name, str);
        }
        return fmt::format("Assignment {}\n     - {}", m_name, str);
    }

    Assignment::Assignment(std::string name, TokenListPtr tokens, bool isarray) :
            m_name(std::move(name)),
            m_tokens(std::move(tokens)),
            m_isarray(isarray) {}

    Assignment::Ptr
    Assignment::create(std::string name, TokenListPtr tokens, bool isarray) {

        return std::unique_ptr<Assignment>(
                new Assignment(std::move(name), std::move(tokens), isarray));
    }

    TokenListPtr Assignment::get_tokens() const {

        return m_tokens;
    }

    bool Assignment::isarray() const {

        return m_isarray;
    }
} // hasha
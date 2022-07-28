//
// Created by mythi on 25/07/22.
//

#ifndef HASHA_PARAMETER_H
#define HASHA_PARAMETER_H


#include <memory>

#include "Token.h"
#include "fmt/format.h"
#include "Identifier.h"

namespace hasha {

    class Parameter : public Token {
        std::string m_name;
        std::string m_type;

        explicit Parameter(std::string name, std::string type) noexcept: m_name(std::move(name)),
                                                                         m_type(std::move(type)) {

        }

    public:
        using ParameterPtr = std::shared_ptr<Parameter>;
        using ParameterList = std::vector<ParameterPtr>;
        using ParameterListPtr = std::shared_ptr<ParameterList>;

        static ParameterListPtr createLsit() {

            return std::make_shared<ParameterList>();
        }

        static nlohmann::json list_to_json(const ParameterListPtr &parameter_list) {

            auto json = nlohmann::json::array();
            for (const auto &param: *parameter_list)
                json.push_back(param->to_json());

            return json;
        }

        static ParameterPtr create(std::string name, std::string type) {

            return std::shared_ptr<Parameter>(new Parameter(std::move(name), std::move(type)));
        }
        

        [[nodiscard]]
        nlohmann::json to_json() const override {

            return {
                    {"token_type", "Parameter"},
                    {"name",       m_name},
                    {"type",       m_type}
            };
        }

        [[nodiscard]]
        std::string to_string() const override {

            return fmt::format("Parameter {} {}", m_name, m_type);
        }

        [[nodiscard]]
        const std::string &get_name() const noexcept {

            return m_name;
        }

        void set_name(const std::string &name) noexcept {

            Parameter::m_name = name;
        }

        [[nodiscard]]
        const std::string &get_m_type() const noexcept {

            return m_type;
        }

        void set_m_type(const std::string &type) noexcept {

            Parameter::m_type = type;
        }
    };

} // hasha

#endif //HASHA_PARAMETER_H

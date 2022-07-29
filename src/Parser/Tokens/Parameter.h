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

        explicit Parameter(std::string name, std::string type) noexcept;

    public:
        using Ptr = std::unique_ptr<Parameter>;
        using ParameterList = std::vector<Ptr>;
        using ParameterListPtr = std::shared_ptr<ParameterList>;

        static ParameterListPtr createLsit();

        static nlohmann::json list_to_json(const ParameterListPtr &parameter_list);

        static Ptr create(std::string name, std::string type);


        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        const std::string &get_name() const noexcept;


        [[nodiscard]]
        const std::string &get_type() const noexcept;

    };

} // hasha

#endif //HASHA_PARAMETER_H

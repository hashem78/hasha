//
// Created by mythi on 11/08/22.
//

#ifndef HASHA_FUNCTIONCALL_H
#define HASHA_FUNCTIONCALL_H

#include "Token.h"
#include "fmt/format.h"

namespace hasha {

    class FunctionCall : public Token {
            std::string m_callee;
            int m_arg_count;
        FunctionCall(std::string callee,int arg_count);
    public:
        using Ptr = std::unique_ptr<FunctionCall>;
        static Ptr create(std::string callee,int arg_count);
        [[nodiscard]] const std::string &get_callee() const;

        [[nodiscard]] int get_arg_count() const;

        [[nodiscard]] nlohmann::json to_json() const override;

        [[nodiscard]] std::string to_string() const override;

    };

} // hasha

#endif //HASHA_FUNCTIONCALL_H

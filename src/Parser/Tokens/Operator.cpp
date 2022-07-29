//
// Created by mythi on 28/07/22.
//

#include "Operator.h"

namespace hasha {
    Operator::Operator(std::string op) noexcept: m_op(std::move(op)) {

    }

    Operator::OperatorPtr Operator::create(std::string op) {

        return std::shared_ptr<Operator>(new Operator(std::move(op)));
    }

    nlohmann::json Operator::to_json() const {

        return {
                {"token_type", "Operator"},
                {"operator",   m_op}
        };
    }

    std::string Operator::to_string() const {

        return fmt::format("Operator {}", m_op);
    }

    const std::string &Operator::get_op() const noexcept {

        return m_op;
    }

} // hasha
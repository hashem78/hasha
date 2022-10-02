//
// Created by mythi on 01/10/22.
//

#include "Function.h"

namespace hasha {
    Function::Function(
            Box<Identifier> name,
            std::vector<Box<Parameter>> parameters,
            std::variant<Box<NormalType>, Box<GenericType>> return_type,
            Box<Block> block,
            Span span,
            int scope_id
    ) noexcept:
            m_name(std::move(name)),
            m_parameters(std::move(parameters)),
            m_return_type(std::move(return_type)),
            m_block(std::move(block)),
            TokenBase(span, scope_id, "Function"sv) {
    }

    const Box<Identifier> &Function::name() const noexcept {

        return m_name;
    }

    const std::variant<Box<NormalType>, Box<GenericType>> &Function::return_type() const noexcept {

        return m_return_type;
    }

    const std::vector<Box<Parameter>> &Function::parameters() const noexcept {

        return m_parameters;
    }

    int Function::number_of_parameters() const noexcept {

        return static_cast<int>(m_parameters.size());
    }

    const Box<Block> &Function::block() const noexcept {

        return m_block;
    }
} // hasha
//
// Created by mythi on 21/07/22.
//

#include "Function.h"


namespace hasha {
    nlohmann::json Function::to_json() const {

        auto json = nlohmann::json();

        json["token_type"] = "Function";
        json["name"] = m_name.get();
        json["return_type"] = m_return_type->to_json();
        json["parameters"] = parameter_list_to_json(m_parameters);
        json["block"] = m_block->to_json();
        json["span"] = m_span.to_json();

        return json;
    }


    Function::Function(
            ParameterList parameters,
            Block::Ptr block,
            Identifier name,
            Type::Ptr return_type,
            const Span &span,
            int scope_id
    )
            : m_parameters(std::move(parameters)),
              m_block(std::move(block)),
              m_return_type(std::move(return_type)),
              m_name(std::move(name)),
              Token(span, scope_id) {
    }

    Function::Ptr Function::create(
            ParameterList parameters,
            Block::Ptr block,
            Identifier name,
            Type::Ptr return_type,
            const Span &span,
            int scope_id
    ) {

        return std::make_unique<Function>(
                std::move(parameters),
                std::move(block),
                std::move(name),
                std::move(return_type),
                span,
                scope_id
        );
    }

    const Identifier& Function::name() const {

        return m_name;
    }

    const Type &Function::return_type() const {

        return *m_return_type;
    }

    const ParameterList &Function::parameters() const {

        return m_parameters;
    }

    const class Block &Function::block() const {

        return *m_block;
    }

    int Function::number_of_parameters() const {

        return static_cast<int>(m_parameters.size());
    }

} // hasha
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
        json["parameters"] = token_list_to_json(m_parameters);
        json["block"] = m_block->to_json();
        json["span"] = m_span.to_json();

        return json;
    }

    const TokenList& Function::get_parameters() const {

        return m_parameters;
    }

    const class Block *Function::get_block() const {

        return m_block.get();
    }


    Function::Function(
            TokenList parameters,
            Block::Ptr block,
            Identifier name,
            Type::Ptr return_type,
            const Span &span
    )
            : m_parameters(std::move(parameters)),
              m_block(std::move(block)),
              m_return_type(std::move(return_type)),
              m_name(std::move(name)),
              Token(span) {
    }

    Function::Ptr Function::create(
            TokenList parameters,
            Block::Ptr block,
            Identifier name,
            Type::Ptr return_type,
            const Span &span
    ) {

        return std::make_unique<Function>(
                std::move(parameters),
                std::move(block),
                std::move(name),
                std::move(return_type),
                span
        );
    }

    Identifier Function::get_name() const {

        return m_name;
    }

    const Type *Function::get_return_type() const {

        return m_return_type.get();
    }

    ErrorOr<void> Function::interpret(Scope::Ptr higher_scope) {
        higher_scope->functions.push_back(m_name.get());

        for(auto& token: m_block->get_tokens()) {
            TRY(token->interpret(m_block->scope()));
        }
        return {};
    }


} // hasha
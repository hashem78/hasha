//
// Created by mythi on 28/07/22.
//

#include "Assignment.h"

#include <memory>

namespace hasha {


    nlohmann::json Assignment::to_json() const {

        auto json = nlohmann::json();

        if (m_isarray) {
            json["token_type"] = "ArrayAssignment";
        } else {
            json["token_type"] = "Assignment";
        }

        json["tokens"] = token_list_to_json(m_tokens.get());

        return json;
    }

    Assignment::Assignment(
            TokenListPtr tokens,
            bool isarray
    ) :
            m_tokens(std::move(tokens)),
            m_isarray(isarray) {}

    Assignment::Ptr Assignment::create(
            TokenListPtr tokens,
            bool isarray
    ) {

        return std::make_unique<Assignment>(
                std::move(tokens),
                isarray

        );
    }

    TokenListPtr Assignment::get_tokens() const {

        return m_tokens;
    }

    bool Assignment::isarray() const {

        return m_isarray;
    }
} // hasha
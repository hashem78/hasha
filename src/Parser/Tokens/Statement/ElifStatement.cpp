//
// Created by mythi on 26/08/22.
//

#include "ElifStatement.h"

namespace hasha {
    ElifStatement::Ptr ElifStatement::create(
            Expression::Ptr condition,
            Block::Ptr block,
            const Span &span
    ) {

        return std::make_unique<ElifStatement>(
                std::move(condition),
                std::move(block),
                span
        );
    }

    nlohmann::json ElifStatement::to_json() const {

        auto json = IfStatement::to_json();
        json["token_type"] = "ElifStatement";
        return json;
    }

} // hasha
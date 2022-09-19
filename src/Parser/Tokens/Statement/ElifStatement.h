//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_ELIFSTATEMENT_H
#define HASHA_ELIFSTATEMENT_H

#include "IfStatement.h"

namespace hasha {

    class ElifStatement : public IfStatement {
        using IfStatement::IfStatement;

    public:
        using Ptr = std::unique_ptr<ElifStatement>;

        static ElifStatement::Ptr create(
                Expression::Ptr condition,
                Block::Ptr block,
                const Span &span,
                int scope_id
        );

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ELIFSTATEMENT_H

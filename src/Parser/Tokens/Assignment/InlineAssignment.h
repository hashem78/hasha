//
// Created by mythi on 17/09/22.
//

#ifndef HASHA_INLINEASSIGNMENT_H
#define HASHA_INLINEASSIGNMENT_H

#include "Assignment.h"
#include "Identifier.h"

namespace hasha {

    class InlineAssignment : public Assignment {
        Identifier::Ptr assignee;
    public:
        using Ptr = std::unique_ptr<InlineAssignment>;

        InlineAssignment(Identifier::Ptr assignee, Expression::Ptr expression, const Span &span);

        static Ptr create(Identifier::Ptr assignee, Expression::Ptr expression, const Span &span);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_INLINEASSIGNMENT_H

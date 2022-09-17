//
// Created by mythi on 17/09/22.
//

#ifndef HASHA_ARRAYINLINEASSIGNMENT_H
#define HASHA_ARRAYINLINEASSIGNMENT_H

#include "Assignment.h"
#include "Identifier.h"

namespace hasha {

    class ArrayInlineAssignment : public Assignment {
        Identifier::Ptr assignee;
        ExpressionList m_expressions;
    public:
        using Ptr = std::unique_ptr<ArrayInlineAssignment>;

        ArrayInlineAssignment(Identifier::Ptr assignee, ExpressionList expressions, const Span &span);

        static Ptr create(Identifier::Ptr assignee, ExpressionList expressions, const Span &span);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ARRAY   INLINEASSIGNMENT_H

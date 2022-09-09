//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_ARRAYASSIGNMENT_H
#define HASHA_ARRAYASSIGNMENT_H

#include "fmt/format.h"
#include "Assignment.h"

namespace hasha {

    class ArrayAssignment : public Assignment {

        ExpressionList m_expressions;

    public:

        explicit ArrayAssignment(
                ExpressionList expressions,
                const Span &span
        );

        using Ptr = std::unique_ptr<ArrayAssignment>;


        static Ptr create(
                ExpressionList expressions,
                const Span &span
        );

        [[nodiscard]]
        const ExpressionList& get_expressions() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

    };

} // hasha

#endif //HASHA_ARRAYASSIGNMENT_H

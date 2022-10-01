//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_TOKENBASE_H
#define HASHA_TOKENBASE_H

#include <vector>
#include "Span.h"

namespace hasha {

    class TokenBase {
        static int number_of_tokens;
    protected:
        Span m_span;
        int id;
        int m_scope_id;

    public:
        explicit TokenBase(const Span &span, int scope_id);

        [[nodiscard]]
        const Span &span() const;

        [[nodiscard]]
        int scope_id() const;

        virtual ~TokenBase() = 0;
    };
} // hasha

#endif //HASHA_TOKENBASE_H

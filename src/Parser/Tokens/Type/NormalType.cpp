//
// Created by mythi on 01/10/22.
//

#include "NormalType.h"

namespace hasha {
    NormalType::NormalType(
            std::string type,
            const Span &span,
            int scope_id
    ) : m_type(std::move(type)),
        TokenBase(span, scope_id) {

    }

    bool NormalType::operator==(const NormalType &other) const {

        return m_type == other.type();
    }

    const std::string &NormalType::type() const {

        return m_type;
    }
} // hasha
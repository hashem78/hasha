//
// Created by mythi on 18/09/22.
//

#ifndef HASHA_GENERICTYPE_H
#define HASHA_GENERICTYPE_H

#include "Type.h"

namespace hasha {

    class GenericType : public Type {
        TypeList m_type_list;
        Span m_span;
    public:
        using Ptr = std::unique_ptr<GenericType>;

        explicit GenericType(
                const std::string &type_name,
                const Span &type_name_span,
                TypeList type_list,
                const Span &span
        );

        static Ptr create(const std::string &type_name,
                          const Span &type_name_span,
                          TypeList type_list,
                          const Span &span
        );

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_GENERICTYPE_H

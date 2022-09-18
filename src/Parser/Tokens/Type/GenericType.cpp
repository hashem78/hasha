//
// Created by mythi on 18/09/22.
//

#include "GenericType.h"

namespace hasha {
    nlohmann::json GenericType::to_json() const {

        auto json = Type::to_json();
        json["token_type"] = "GenericType";
        json["type_list"] = type_list_to_json(m_type_list);
        return json;
    }

    GenericType::GenericType(
            const std::string &type_name,
            const Span &type_name_span,
            TypeList type_list,
            const Span &span
    ) :
            m_type_list(std::move(type_list)),
            m_span(span),
            Type(type_name, type_name_span) {

    }

    GenericType::Ptr GenericType::create(
            const std::string &type_name,
            const Span &type_name_span,
            TypeList type_list,
            const Span &span
    ) {

        return std::make_unique<GenericType>(type_name, type_name_span, std::move(type_list), span);
    }


} // hasha
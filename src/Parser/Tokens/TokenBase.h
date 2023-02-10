//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_TOKENBASE_H
#define HASHA_TOKENBASE_H

#include "Span.h"
#include <string>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;

namespace hasha {

  class TokenBase {
    static int number_of_tokens;
    std::string_view m_type;

   protected:
    Span m_span;
    int id;
    int m_scope_id;

   public:
    explicit TokenBase(const Span &span, int scope_id, std::string_view type);

    [[nodiscard]] const Span &span() const;

    [[nodiscard]] int scope_id() const;

    [[nodiscard]] std::string_view token_type() const;

    virtual ~TokenBase() = 0;
  };
}// namespace hasha

#endif//HASHA_TOKENBASE_H

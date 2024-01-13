//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_TOKENBASE_H
#define HASHA_TOKENBASE_H

#include "Helpers.h"
#include "Span.h"
#include "uuid.h"
#include <concepts>
#include <type_traits>

using namespace std::string_view_literals;

#define DEFINE_DETAILS()                  \
 private:                                 \
  TokenDetails m_details;                 \
                                          \
 public:                                  \
  TokenDetails details() const noexcept { \
    return m_details;                     \
  }                                       \
                                          \
 private:

#define CONSTRUCT_DETAILS(TOKEN_NAME) \
  m_details(#TOKEN_NAME ##sv, span, std::move(scope_id))

namespace hasha {


  struct [[nodiscard]] TokenDetails final {
    std::string_view name;
    Span span;
    uuids::uuid scope_id;
    uuids::uuid id;

    explicit TokenDetails(
      std::string_view name,
      Span span,
      uuid scope_id
    ) noexcept
        : name(name),
          span(span),
          scope_id(std::move(scope_id)),
          id(generate_uuid()) {
    }
  };

  template<typename T>
  concept TokenConcept = requires(T t) {
    { noexcept(t.details()) } -> std::same_as<hasha::TokenDetails>;
  };
}// namespace hasha

#endif//HASHA_TOKENBASE_H

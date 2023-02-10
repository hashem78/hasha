//
// Created by mythi on 21/07/22.
//

#include "TokenBase.h"

namespace hasha {

  TokenBase::TokenBase(
    const Span &span,
    int scope_id,
    std::string_view type
  )
      : m_span(span),
        m_type(type),
        m_scope_id(scope_id),
        id(number_of_tokens++) {
  }


  const Span &TokenBase::span() const {

    return m_span;
  }

  int TokenBase::scope_id() const {

    return m_scope_id;
  }

  TokenBase::~TokenBase() = default;

  int TokenBase::number_of_tokens = 0;

  std::string_view TokenBase::token_type() const {

    return m_type;
  }
}// namespace hasha
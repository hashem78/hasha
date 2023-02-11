//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_NORMALTYPE_H
#define HASHA_NORMALTYPE_H

#include "TokenBase.h"
#include <string>

namespace hasha {

  class [[nodiscard]] NormalType final {
    std::string m_type;
    DEFINE_DETAILS()

   public:
    NormalType(
      std::string type,
      Span span,
      uuid scope_id
    );

    bool operator==(const NormalType &other) const;

    [[nodiscard]] const std::string &type() const;
  };
}// namespace hasha

#endif//HASHA_NORMALTYPE_H

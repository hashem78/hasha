//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_NORMALTYPE_H
#define HASHA_NORMALTYPE_H

#include "TokenBase.h"
#include <string>

namespace hasha {

  class NormalType : public TokenBase {
    std::string m_type;

   public:
    NormalType(
      std::string type,
      const Span &span,
      int scope_id
    );

    bool operator==(const NormalType &other) const;

    [[nodiscard]] const std::string &type() const;
  };
}// namespace hasha

#endif//HASHA_NORMALTYPE_H

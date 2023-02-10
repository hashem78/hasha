//
// Created by mythi on 02/10/22.
//

#ifndef HASHA_SERIALIZER_H
#define HASHA_SERIALIZER_H

#include "Block.h"
#include "nlohmann/json.hpp"

namespace hasha {

  class Serializer {
    BoxedBlock global_block;
    std::string_view save_location;
    nlohmann::ordered_json json;

   public:
    explicit Serializer(
      BoxedBlock block,
      std::string_view location = "output.json"sv
    ) noexcept;

    void serialize() noexcept;

    void dump() const;
  };

}// namespace hasha

#endif//HASHA_SERIALIZER_H

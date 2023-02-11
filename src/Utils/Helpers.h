#pragma once

#include "uuid.h"

namespace hasha {

  using uuids::uuid;

  [[nodiscard]] inline uuid generate_uuid() {
    return uuids::uuid_system_generator{}();
  }

}// namespace hasha
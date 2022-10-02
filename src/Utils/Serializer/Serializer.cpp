//
// Created by mythi on 02/10/22.
//

#include <fstream>
#include "Serializer.h"
#include "JsonConverter.h"

namespace hasha {
    Serializer::Serializer(
            BoxedBlock block,
            std::string_view
            location
    ) noexcept:
            global_block(std::move(block)),
            save_location(location),
            json(nlohmann::ordered_json::array()) {

    }

    void Serializer::serialize() noexcept {

        for (const auto &token: global_block->tokens()) {

            json.push_back(std::visit(JsonConverter{}, token));

        }

    }

    void Serializer::dump() const {

        std::ofstream ofile(save_location.data());
        if (ofile.is_open() && ofile.good())
            ofile << std::setw(4) << json;
    }
} // hasha
//
// Created by mythi on 02/09/22.
//

#ifndef HASHA_SPAN_H
#define HASHA_SPAN_H

#include "nlohmann/json.hpp"

namespace hasha {

  struct Span {
    int begin;
    int end;
    int line;
    int col;

    bool operator==(const Span &) const = default;

    explicit constexpr Span(
      int begin = 0,
      int end = 0,
      int line = 0,
      int col = 0
    )
        : begin(begin),
          end(end),
          line(line),
          col(col) {
    }

    [[nodiscard]] nlohmann::json to_json() const noexcept {

      return {
        {"begin", begin},
        {"end", end},
        {"line", line},
        {"col", col}};
    }

    [[nodiscard]] Span merge_with(Span other) const {
      return Span{
        begin,
        other.end,
        line,
        col};
    }
  };
}// namespace hasha

#endif//HASHA_SPAN_H

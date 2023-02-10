//
// Created by mythi on 03/09/22.
//

#include <stack>
#include <vector>

#include "fmt/core.h"

#include "Analyzer.h"
#include "Constants.h"


namespace hasha {
  Analyzer::Analyzer(const LexemeList &lexemes)
      : lexemes(lexemes) {
  }

  ErrorOr<void> Analyzer::analyze_bracket_pairs() {


    auto analyze_pair = [this](const Lexeme &open, const Lexeme &close) -> ErrorOr<void> {
      std::stack<Lexeme> stk;

      for (const auto &lexeme: lexemes) {

        if (lexeme != open && lexeme != close) [[likely]]
          continue;

        if (stk.empty()) {
          stk.push(lexeme);
        } else if (stk.top() == open && lexeme == close) {

          stk.pop();
        } else {
          stk.push(lexeme);
        }
      }

      if (stk.empty()) {
        return {};
      }

      return fmt::format(
        "Mismatched {} on line: {}, col: {}",
        stk.top().data(),
        stk.top().span().line,
        stk.top().span().col
      );
    };

    TRY(analyze_pair(LCURLY, RCURLY));
    TRY(analyze_pair(LPAREN, RPAREN));
    TRY(analyze_pair(LBRACKET, RBRACKET));

    return {};
  }
}// namespace hasha
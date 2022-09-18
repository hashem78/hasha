//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_PATTERN_H
#define HASHA_PATTERN_H

#include <array>

#include <variant>
#include "Lexeme.h"
#include "Constants.h"

namespace hasha::Patterns {

    // The result of the matching functor and the edit to the cursor
    struct FunctorResult {
        bool matched;
        int cursor;
    };

    using PatternType = std::variant<LexemeType, Lexeme>;

    template<class... Ts>
    struct PatternVisitor : Ts ... {
        using Ts::operator()...;
    };
    template<class... Ts> PatternVisitor(Ts...) -> PatternVisitor<Ts...>;

    using Pattern = std::vector<PatternType>;

    inline const Pattern FunctionCall{
            LexemeType::IDENTIFIER,
            LPAREN
    };

    inline const Pattern LiteralTypes{
            LexemeType::NUMERIC_LITERAL,
            LexemeType::BOOLEAN_LITERAL,
            LexemeType::STRING_LITERAL
    };

    inline const Pattern Declaration {
            LexemeType::IDENTIFIER,
            COLON,
            LexemeType::IDENTIFIER
    };

}

#endif //HASHA_PATTERN_H

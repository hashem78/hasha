//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_PATTERN_H
#define HASHA_PATTERN_H

#include <array>

#include <variant>
#include "Lexeme.h"
#include "LexerTypes.h"
#include "Constants.h"

namespace hasha::Patterns {

    using PatternType = std::variant<LexemeType, Lexeme>;

    template<class... Ts>
    struct PatternVisitor : Ts ... {
        using Ts::operator()...;
    };
    template<class... Ts> PatternVisitor(Ts...) -> PatternVisitor<Ts...>;

    using Pattern = std::vector<PatternType>;

    inline const Pattern Assignment{
            LexemeType::IDENTIFIER,
            EQUALS
    };

    inline const Pattern FunctionCall{
            LexemeType::IDENTIFIER,
            LPAREN
    };

    inline const Pattern GenericType{
            LexemeType::IDENTIFIER,
            LANGEL
    };

    inline const Pattern Declaration{
            LexemeType::IDENTIFIER,
            COLON,
            LexemeType::IDENTIFIER
    };

}

#endif //HASHA_PATTERN_H

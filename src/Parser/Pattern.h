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

    using PatternFunctor = std::function<FunctorResult(const LexemeList &, int)>;
    using PatternType = std::variant<LexemeType, Lexeme, PatternFunctor>;

    template<class... Ts>
    struct PatternVisitor : Ts ... {
        using Ts::operator()...;
    };
    template<class... Ts> PatternVisitor(Ts...) -> PatternVisitor<Ts...>;

    template<size_t S>
    using Pattern = std::array<PatternType, S>;

    inline const Pattern<2> FunctionCall{
            LexemeType::IDENTIFIER,
            LPAREN
    };

    inline const Pattern<3> LiteralTypes{
            LexemeType::NUMERIC_LITERAL,
            LexemeType::BOOLEAN_LITERAL,
            LexemeType::STRING_LITERAL
    };

    inline const Pattern<3> Declaration {
            LexemeType::IDENTIFIER,
            LexemeType::IDENTIFIER,
            SEMICOLON
    };

    inline const Pattern<3> DeclarationWithAssignment {
            LexemeType::IDENTIFIER,
            LexemeType::IDENTIFIER,
            EQUALS
    };
    
    inline Pattern<2> InlineAssignment {
            LexemeType::IDENTIFIER,
            EQUALS
    };

}

#endif //HASHA_PATTERN_H

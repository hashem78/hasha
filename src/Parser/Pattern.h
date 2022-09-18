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

    template<class... Ts>
    struct PatternVisitor : Ts ... {
        using Ts::operator()...;
    };
    template<class... Ts> PatternVisitor(Ts...) -> PatternVisitor<Ts...>;

    using PatternType = std::variant<LexemeType, Lexeme>;
    using Pattern = std::vector<PatternType>;
    using MultiPattern = std::vector<Pattern>;
    using NestedPattern = std::vector<std::variant<Pattern, MultiPattern, LexemeType, Lexeme>>;

    inline const
    Pattern FunctionCall{
            LexemeType::IDENTIFIER,
            LPAREN
    };

    inline const Pattern LiteralTypes{
            LexemeType::NUMERIC_LITERAL,
            LexemeType::BOOLEAN_LITERAL,
            LexemeType::STRING_LITERAL
    };


    inline const Pattern DeclarationWithAssignment{
            LexemeType::IDENTIFIER,
            LexemeType::IDENTIFIER,
            EQUALS
    };

    inline const Pattern ValueType{
            LexemeType::IDENTIFIER
    };

    inline const Pattern ArrayType{
            LexemeType::IDENTIFIER,
            LBRACKET,
            RBRACKET
    };

    inline const Pattern PointerType{
            LexemeType::IDENTIFIER,
            ASTERISK
    };

    inline const MultiPattern Type{
            ValueType,
            ArrayType,
            PointerType
    };

    inline const NestedPattern Declaration{
            Type,
            LexemeType::IDENTIFIER
    };
}

#endif //HASHA_PATTERN_H

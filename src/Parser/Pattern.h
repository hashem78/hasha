//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_PATTERN_H
#define HASHA_PATTERN_H

#include <array>
#include <variant>
#include "Lexeme.h"

namespace hasha::Patterns {
    template<size_t S>
    using Pattern = std::array<std::variant<LexemeType, Lexeme>, S>;

    constexpr Pattern<2> VariableAssignment{LexemeType::Identifier, EQUALS};
    constexpr Pattern<3> VariableDeclaration{LexemeType::Identifier, LexemeType::Identifier, SEMICOLON};
    constexpr Pattern<3> VariableDeclarationAndAssignment{LexemeType::Identifier, LexemeType::Identifier, EQUALS};
    constexpr Pattern<5> ArrayDeclaration{
            LexemeType::Identifier,
            LBRACKET,
            RBRACKET,
            LexemeType::Identifier,
            SEMICOLON
    };
    constexpr Pattern<5> ArrayDeclarationAndAssignment{
            LexemeType::Identifier,
            LBRACKET,
            RBRACKET,
            LexemeType::Identifier,
            EQUALS
    };
}

#endif //HASHA_PATTERN_H

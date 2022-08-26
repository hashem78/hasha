//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_PATTERN_H
#define HASHA_PATTERN_H

#include <array>
#include <utility>
#include <variant>
#include "Lexeme.h"
#include "Constants.h"

namespace hasha::Patterns {
    enum class FunctorState {
        MATCH,
        NO_MATCH,
    };
    // The result of the matching functor and the edit to the cursor
    struct FunctorResult {
        FunctorState state;
        int cursor;
    };


    using PatternFunctor = std::function<FunctorResult(const LexemeList &, int)>;
    using PatternType = std::variant<LexemeType, Lexeme, PatternFunctor>;
    template<size_t S>
    using Pattern = std::array<PatternType, S>;

    inline const Pattern<2> VariableAssignment{LexemeType::IDENTIFIER, EQUALS};
    inline const Pattern<3> VariableDeclaration{LexemeType::IDENTIFIER, LexemeType::IDENTIFIER, SEMICOLON};
    inline const Pattern<3> VariableDeclarationAndAssignment{LexemeType::IDENTIFIER, LexemeType::IDENTIFIER, EQUALS};
    inline const Pattern<5> ArrayDeclaration{
            LexemeType::IDENTIFIER,
            LBRACKET,
            RBRACKET,
            LexemeType::IDENTIFIER,
            SEMICOLON
    };
    inline const Pattern<5> ArrayDeclarationAndAssignment{
            LexemeType::IDENTIFIER,
            LBRACKET,
            RBRACKET,
            LexemeType::IDENTIFIER,
            EQUALS
    };
    inline const Pattern<2> FunctionCall{
            LexemeType::IDENTIFIER,
            LPAREN
    };

    inline const Pattern<6> FunctionDefinition{

            IDENTIFIER,
            LPAREN,
            [](const LexemeList &lexemes, int cursor) -> FunctorResult {
                int i = cursor + 2;
                while (lexemes[i] != RPAREN) {
                    if (lexemes[i].get_type() != IDENTIFIER && lexemes[i] != COMMA) {
                        fmt::print("Did not match because of {}\n", lexemes[i].to_string());
                        return {FunctorState::NO_MATCH, 0};
                    }
                    i++;
                };
                return {FunctorState::MATCH, i - cursor - 3};
            },
            RPAREN,
            ARROW,
            IDENTIFIER
    };
}

#endif //HASHA_PATTERN_H

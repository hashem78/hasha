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

    class PatternFunctor {
        const Lexeme m_lexeme;
    public:
        constexpr explicit PatternFunctor(Lexeme lexeme) : m_lexeme(lexeme) {

        }

        bool call(const LexemeList &lexemes, int from) {

            for (int i = from; i < lexemes.size(); ++i) {
                if (lexemes[i] == m_lexeme)
                    return true;
            }
            return false;
        }
    };

    using PatternType = std::variant<LexemeType, Lexeme, PatternFunctor>;
    template<size_t S>
    using Pattern = std::array<PatternType, S>;

     inline const Pattern<2> VariableAssignment{LexemeType::Identifier, EQUALS};
     inline const Pattern<3> VariableDeclaration{LexemeType::Identifier, LexemeType::Identifier, SEMICOLON};
     inline const Pattern<3> VariableDeclarationAndAssignment{LexemeType::Identifier, LexemeType::Identifier, EQUALS};
     inline const Pattern<5> ArrayDeclaration{
            LexemeType::Identifier,
            LBRACKET,
            RBRACKET,
            LexemeType::Identifier,
            SEMICOLON
    };
     inline const Pattern<5> ArrayDeclarationAndAssignment{
            LexemeType::Identifier,
            LBRACKET,
            RBRACKET,
            LexemeType::Identifier,
            EQUALS
    };
    constexpr Pattern<2> FunctionCall{
            LexemeType::Identifier,
            LPAREN
    };
}

#endif //HASHA_PATTERN_H

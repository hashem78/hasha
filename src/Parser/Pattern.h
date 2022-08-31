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

    template<size_t S>
    using Pattern = std::array<PatternType, S>;

    inline const Pattern<3> VariableDeclaration{
            LexemeType::IDENTIFIER,
            LexemeType::IDENTIFIER,
            SEMICOLON
    };

    inline const Pattern<5> ArrayDeclaration{
            LexemeType::IDENTIFIER,
            LBRACKET,
            RBRACKET,
            LexemeType::IDENTIFIER,
            SEMICOLON
    };

    inline const Pattern<2> VariableAssignment{LexemeType::IDENTIFIER, EQUALS};
    inline const Pattern<3> VariableDeclarationAndAssignment{LexemeType::IDENTIFIER, LexemeType::IDENTIFIER, EQUALS};

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

            LexemeType::IDENTIFIER,
            LPAREN,
            [](const LexemeList &lexemes, int cursor) -> FunctorResult {
                int i = cursor + 2;
                while (lexemes[i] != RPAREN) {
                    if (lexemes[i].type() != LexemeType::IDENTIFIER && lexemes[i] != COMMA) {
                        fmt::print("Did not match because of {}\n", lexemes[i].to_string());
                        return {false, 0};
                    }
                    i++;
                };
                return {true, i - cursor - 3};
            },
            RPAREN,
            ARROW,
            LexemeType::IDENTIFIER
    };
    inline const Pattern<1> IfStatement{
            IF,
    };
    inline const Pattern<1> ElifStatement{
            ELIF,
    };
    inline const Pattern<1> ElseStatement{
            ELSE,
    };
}

#endif //HASHA_PATTERN_H

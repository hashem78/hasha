//
// Created by mythi on 11/08/22.
//

#ifndef HASHA_CONSTANTS_H
#define HASHA_CONSTANTS_H
#include "Lexeme.h"
namespace hasha {
    inline const Lexeme FN{"fn", LexemeType::Keyword};
    inline const Lexeme RETURN{"return", LexemeType::Keyword};
    inline const Lexeme TRUE{"true", LexemeType::Keyword, false, true};
    inline const Lexeme FALSE{"false", LexemeType::Keyword, false, true};
    inline const Lexeme LCURLY{"{", LexemeType::Symbol};
    inline const Lexeme RCURLY{"}", LexemeType::Symbol};
    inline const Lexeme LPAREN{"(", LexemeType::Symbol};
    inline const Lexeme RPAREN{")", LexemeType::Symbol};
    inline const Lexeme LBRACKET{"[", LexemeType::Symbol};
    inline const Lexeme RBRACKET{"]", LexemeType::Symbol};
    inline const Lexeme COMMA{",", LexemeType::Symbol};
    inline const Lexeme SEMICOLON{";", LexemeType::Symbol};
    inline const Lexeme EQUALS{"=", LexemeType::Operator, Associativity::Right, Precedence::Level1};
    inline const Lexeme LAND{"&&", LexemeType::Operator, Associativity::Right, Precedence::Level2, false, true};
    inline const Lexeme LOR{"||", LexemeType::Operator, Associativity::Right, Precedence::Level2, false, true};

    inline const Lexeme HYPHEN{"-", LexemeType::Operator, Associativity::Left, Precedence::Level3, true};
    inline const Lexeme ADDITION{"+", LexemeType::Operator, Associativity::Left, Precedence::Level3, true};
    inline const Lexeme FSLASH{"/", LexemeType::Operator, Associativity::Left, Precedence::Level5, true};
    inline const Lexeme ASTERISK{"*", LexemeType::Operator, Associativity::Left, Precedence::Level5, true};

    inline const Lexeme ARROW{"->", LexemeType::Symbol};
}

#endif //HASHA_CONSTANTS_H

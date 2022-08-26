//
// Created by mythi on 11/08/22.
//

#ifndef HASHA_CONSTANTS_H
#define HASHA_CONSTANTS_H
#include "Lexeme.h"
namespace hasha {
    inline const Lexeme FN{"fn", LexemeType::KEYWORD};
    inline const Lexeme IF{"if", LexemeType::KEYWORD};
    inline const Lexeme RETURN{"return", LexemeType::KEYWORD};
    inline const Lexeme TRUE{"true", LexemeType::KEYWORD, false, true};
    inline const Lexeme FALSE{"false", LexemeType::KEYWORD, false, true};
    inline const Lexeme LCURLY{"{", LexemeType::SYMBOL};
    inline const Lexeme RCURLY{"}", LexemeType::SYMBOL};
    inline const Lexeme LPAREN{"(", LexemeType::SYMBOL};
    inline const Lexeme RPAREN{")", LexemeType::SYMBOL};
    inline const Lexeme LBRACKET{"[", LexemeType::SYMBOL};
    inline const Lexeme RBRACKET{"]", LexemeType::SYMBOL};
    inline const Lexeme COMMA{",", LexemeType::SYMBOL};
    inline const Lexeme SEMICOLON{";", LexemeType::SYMBOL};
    inline const Lexeme EQUALS{"=", LexemeType::OPERATOR, Associativity::Right, Precedence::Level1};
    inline const Lexeme LAND{"&&", LexemeType::OPERATOR, Associativity::Right, Precedence::Level2, false, true};
    inline const Lexeme LOR{"||", LexemeType::OPERATOR, Associativity::Right, Precedence::Level2, false, true};

    inline const Lexeme HYPHEN{"-", LexemeType::OPERATOR, Associativity::Left, Precedence::Level3, true};
    inline const Lexeme ADDITION{"+", LexemeType::OPERATOR, Associativity::Left, Precedence::Level3, true};
    inline const Lexeme FSLASH{"/", LexemeType::OPERATOR, Associativity::Left, Precedence::Level5, true};
    inline const Lexeme ASTERISK{"*", LexemeType::OPERATOR, Associativity::Left, Precedence::Level5, true};

    inline const Lexeme ARROW{"->", LexemeType::SYMBOL};
}

#endif //HASHA_CONSTANTS_H

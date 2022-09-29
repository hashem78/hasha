//
// Created by mythi on 11/08/22.
//

#ifndef HASHA_CONSTANTS_H
#define HASHA_CONSTANTS_H

#include "Lexeme.h"

namespace hasha {
    inline const Lexeme ILLEGAL{"", LexemeType::ILLEGAL};
    inline const Lexeme EOFL{"", LexemeType::EOFT};
    inline const Lexeme FN{"fn", LexemeType::KEYWORD};
    inline const Lexeme IF{"if", LexemeType::KEYWORD};
    inline const Lexeme ELSE{"else", LexemeType::KEYWORD};
    inline const Lexeme ELIF{"elif", LexemeType::KEYWORD};
    inline const Lexeme RETURN{"return", LexemeType::KEYWORD};
    inline const Lexeme TRUE{"true", LexemeType::BOOLEAN_LITERAL};
    inline const Lexeme FALSE{"false", LexemeType::BOOLEAN_LITERAL};
    inline const Lexeme LCURLY{"{", LexemeType::SYMBOL};
    inline const Lexeme RCURLY{"}", LexemeType::SYMBOL};
    inline const Lexeme LPAREN{"(", LexemeType::SYMBOL};
    inline const Lexeme RPAREN{")", LexemeType::SYMBOL};
    inline const Lexeme LANGEL{"<", LexemeType::SYMBOL};
    inline const Lexeme RANGEL{">", LexemeType::SYMBOL};
    inline const Lexeme LBRACKET{"[", LexemeType::SYMBOL};
    inline const Lexeme RBRACKET{"]", LexemeType::SYMBOL};
    inline const Lexeme COMMA{",", LexemeType::SYMBOL};
    inline const Lexeme SEMICOLON{";", LexemeType::SYMBOL};
    inline const Lexeme COLON{":", LexemeType::SYMBOL};
    inline const Lexeme ARROW{"->", LexemeType::SYMBOL};
    inline const Lexeme EQUALS{
            "=",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::RIGHT,
            Precedence::LVL1
    };
    inline const Lexeme LAND{
            "&&",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::RIGHT,
            Precedence::LVL2
    };
    inline const Lexeme LOR{
            "||",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::RIGHT,
            Precedence::LVL2
    };
    inline const Lexeme FSLASH{
            "/",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::LEFT,
            Precedence::LVL5
    };
    inline const Lexeme ASTERISK{
            "*",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::LEFT,
            Precedence::LVL5
    };
    inline const Lexeme UNARY_MINUS{
            "-",
            LexemeType::OPERATOR,
            OperatorType::UNARY,
            Associativity::RIGHT,
            Precedence::LVL6
    };
    inline const Lexeme UNARY_PLUS{
            "+",
            LexemeType::OPERATOR,
            OperatorType::UNARY,
            Associativity::RIGHT,
            Precedence::LVL6
    };
    inline const Lexeme BINARY_MINUS{
            "-",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::LEFT,
            Precedence::LVL3
    };
    inline const Lexeme BINARY_PLUS{
            "+",
            LexemeType::OPERATOR,
            OperatorType::BINARY,
            Associativity::LEFT,
            Precedence::LVL3
    };
}

#endif //HASHA_CONSTANTS_H

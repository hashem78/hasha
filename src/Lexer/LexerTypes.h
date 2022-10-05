//
// Created by mythi on 24/09/22.
//

#ifndef HASHA_LEXERTYPES_H
#define HASHA_LEXERTYPES_H

namespace hasha {
    enum class LexemeType {
        OPERATOR,
        IDENTIFIER,
        LITERAL,
        SYMBOL,
        KEYWORD,
        ILLEGAL,
        EOFT,
    };
    enum class LexLitrealType {
        BOOLEAN_LITERAL,
        INTEGER_LITERAL,
        FLOATINGPOINT_LITERAL,
        STRING_LITERAL
    };

    enum class Associativity {
        LEFT,
        RIGHT,
        NONE
    };
    enum class Precedence {
        LVL6 = 6,
        LVL5 = 5,
        LVL4 = 4,
        LVL3 = 3,
        LVL2 = 2,
        LVL1 = 1,
        NONE = 0
    };
}

#endif //HASHA_LEXERTYPES_H

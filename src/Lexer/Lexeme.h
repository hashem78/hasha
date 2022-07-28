//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_LEXEME_H
#define HASHA_LEXEME_H

#include <string>
#include <deque>
#include <utility>

#include "nlohmann/json.hpp"
#include "magic_enum.hpp"
#include "fmt/format.h"

namespace hasha {

    enum LexemeType {
        Operator,
        Identifier,
        Literal,
        Symbol,
        Keyword,
    };

    enum Associativity {
        Left,
        Right,
        None
    };
    enum Precedence {
        Level6 = 6,
        Level5 = 5,
        Level4 = 4,
        Level3 = 3,
        Level2 = 2,
        Level1 = 1,
        Level0 = 0
    };

    class Lexeme {
        std::string m_data;
        LexemeType m_type;
        Associativity m_associativity;
        Precedence m_precedence;

    public:

        Lexeme(std::string data, LexemeType type, Associativity= Associativity::None, Precedence= Precedence::Level0);

        auto operator<=>(const Lexeme &) const = default;

        [[nodiscard]]
        nlohmann::json to_json() const;

        [[nodiscard]]
        std::string to_string() const;

        [[nodiscard]]
        const std::string &get_data() const;

        [[nodiscard]]
        LexemeType get_type() const;

        [[nodiscard]]
        Precedence get_precedence() const;

        [[nodiscard]]
        Associativity get_associativity() const;

        const static Lexeme FN;
        const static Lexeme LCURLY;
        const static Lexeme RCURLY;
        const static Lexeme LPAREN;
        const static Lexeme RPAREN;
        const static Lexeme LBRACKET;
        const static Lexeme RBRACKET;
        const static Lexeme ADDITION;
        const static Lexeme HYPHEN;
        const static Lexeme ASTERISK;
        const static Lexeme FSLASH;
        const static Lexeme COMMA;
        const static Lexeme SEMICOLON;
        const static Lexeme EQUALS;
    };


    using LexemeList = std::deque<Lexeme>;
    using LexemeListItr = LexemeList::const_iterator;

} // hasha

#endif //HASHA_LEXEME_H

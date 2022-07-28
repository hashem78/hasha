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
        const char *m_data;
        LexemeType m_type;
        Associativity m_associativity;
        Precedence m_precedence;

    public:

        constexpr Lexeme(
                const char *data,
                LexemeType type,
                Associativity associativity = Associativity::None,
                Precedence precedence = Precedence::Level0) :
                m_data(data),
                m_type(type),
                m_associativity(associativity),
                m_precedence(precedence) {}

        constexpr auto operator<=>(const Lexeme &) const = default;

        [[nodiscard]]
        nlohmann::json to_json() const;

        [[nodiscard]]
        std::string to_string() const;

        [[nodiscard]]
        std::string get_data() const;

        [[nodiscard]]
        LexemeType get_type() const;

        [[nodiscard]]
        Precedence get_precedence() const;

        [[nodiscard]]
        Associativity get_associativity() const;


    };

    static constexpr Lexeme FN{"fn", LexemeType::Keyword};
    static constexpr Lexeme LCURLY{"{", LexemeType::Symbol};
    static constexpr Lexeme RCURLY{"}", LexemeType::Symbol};
    static constexpr Lexeme LPAREN{"(", LexemeType::Symbol};
    static constexpr Lexeme RPAREN{")", LexemeType::Symbol};
    static constexpr Lexeme LBRACKET{"[", LexemeType::Symbol};
    static constexpr Lexeme RBRACKET{"]", LexemeType::Symbol};
    static constexpr Lexeme COMMA{",", LexemeType::Symbol};
    static constexpr Lexeme SEMICOLON{";", LexemeType::Symbol};
    static constexpr Lexeme EQUALS{"=", LexemeType::Operator, Associativity::Right, Precedence::Level1};
    static constexpr Lexeme HYPHEN{"-", LexemeType::Operator, Associativity::Left, Precedence::Level3};
    static constexpr Lexeme ADDITION{"+", LexemeType::Operator, Associativity::Left, Precedence::Level3};
    static constexpr Lexeme FSLASH{"/", LexemeType::Operator, Associativity::Left, Precedence::Level5};
    static constexpr Lexeme ASTERISK{"*", LexemeType::Operator, Associativity::Left, Precedence::Level6};


    using LexemeList = std::deque<Lexeme>;
    using LexemeListItr = LexemeList::const_iterator;

} // hasha

#endif //HASHA_LEXEME_H

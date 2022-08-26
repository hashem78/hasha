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
        OPERATOR,
        IDENTIFIER,
        LITERAL,
        SYMBOL,
        KEYWORD,
        ILLEGAL,
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
        static int id_counter;
        int m_id;
        std::string m_data;
        LexemeType m_type;
        Associativity m_associativity;
        Precedence m_precedence;
        bool m_isstring;
        bool m_isboolean;
        bool m_is_numeric_operator;
        bool m_is_boolean_operator;

    public:

        Lexeme(
                std::string data,
                LexemeType type,
                Associativity associativity,
                Precedence precedence,
                bool is_numeric_operator = false,
                bool is_boolean_operator = false
        ) :
                m_id(id_counter++),
                m_data(std::move(data)),
                m_type(type),
                m_associativity(associativity),
                m_precedence(precedence),
                m_isstring(false),
                m_isboolean(false),
                m_is_numeric_operator(is_numeric_operator),
                m_is_boolean_operator(is_boolean_operator) {}

        Lexeme(
                std::string data,
                LexemeType type,
                bool isstring = false,
                bool isboolean = false
        ) :
                m_id(id_counter++),
                m_data(std::move(data)),
                m_type(type),
                m_associativity(Associativity::None),
                m_precedence(Precedence::Level0), m_isstring(isstring),
                m_isboolean(isboolean),
                m_is_numeric_operator(false),
                m_is_boolean_operator(false) {}


        auto operator<=>(const Lexeme &) const = default;

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

        [[nodiscard]]
        bool is_string() const;

        [[nodiscard]]
        bool is_boolean() const;

        [[nodiscard]]
        bool is_numeric_operator() const;

        [[nodiscard]]
        bool is_boolean_operator() const;

        [[nodiscard]]
        int get_id() const noexcept;
    };

    using LexemeList = std::deque<Lexeme>;

} // hasha

#endif //HASHA_LEXEME_H

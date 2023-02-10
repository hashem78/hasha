//
// Created by mythi on 28/07/22.
//

#ifndef HASHA_PATTERN_H
#define HASHA_PATTERN_H

#include <array>

#include "Constants.h"
#include "Lexeme.h"
#include "LexerTypes.h"
#include <variant>

namespace hasha::Patterns {

  using PatternType = std::variant<LexemeType, Lexeme>;

  using Pattern = std::vector<PatternType>;

  inline const Pattern Assignment{
    LexemeType::IDENTIFIER,
    EQUALS};

  inline const Pattern FunctionCall{
    LexemeType::IDENTIFIER,
    LPAREN};

  inline const Pattern GenericType{
    LexemeType::IDENTIFIER,
    LANGEL};

  inline const Pattern Declaration{
    LexemeType::IDENTIFIER,
    COLON,
    LexemeType::IDENTIFIER};

}// namespace hasha::Patterns

#endif//HASHA_PATTERN_H

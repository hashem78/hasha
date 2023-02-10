//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_TOKEN_H
#define HASHA_TOKEN_H

#include "Box.h"
#include "TokenForwards.h"
#include <variant>
#include <vector>

namespace hasha {
  using Token = std::variant<
    Box<Identifier>,
    std::variant<Box<NormalType>, Box<GenericType>>,
    Box<Expression>,
    Box<Declaration>,
    Box<Literal>,
    Box<Operator>,
    Box<FunctionCall>,
    Box<Block>,
    Box<Function>,
    Box<Assignment>,
    Box<Parameter>,
    Box<IfStatement>,
    Box<ElifStatement>,
    Box<ElseStatement>,
    Box<ReturnToken>>;
  using TokenList = std::vector<Token>;
}// namespace hasha

#endif//HASHA_TOKEN_H

//
// Created by mythi on 01/10/22.
//

#ifndef HASHA_TOKEN_H
#define HASHA_TOKEN_H

#include <variant>
#include <vector>
#include "Box.h"
#include "TokenForwards.h"

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
            Box<ElseStatement>
    >;
    using TokenList = std::vector<Token>;
}

#endif //HASHA_TOKEN_H

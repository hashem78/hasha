//
// Created by mythi on 22/07/22.
//

#include "Expression.h"

namespace hasha {

    ExpressionListPtr create_expression_list() {

        return std::make_shared<ExpressionList>();
    }
} // hasha
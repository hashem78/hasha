//
// Created by mythi on 28/09/22.
//

#ifndef HASHA_DEFAULTOPERATIONS_H
#define HASHA_DEFAULTOPERATIONS_H


#include "DefaultTypes.h"

namespace hasha {

    enum class HashaNumberUnaryOperation {
        Negation
    };

    struct HashaUnaryOperatorVisitor {
        HashaNumberUnaryOperation operation_type;

        constexpr explicit HashaUnaryOperatorVisitor(HashaNumberUnaryOperation op) :
                operation_type(op) {

        }

        constexpr HashaNumber operator()(auto A) const {

            switch (operation_type) {

                case HashaNumberUnaryOperation::Negation:
                    return -A;

            }
            return {};
        }
    };

    enum class HashaNumberBinaryOperation {
        Multiplication,
        Divison,
        Addition,
        Subtraction
    };

    struct HashaBinaryOperatorVisitor {
        HashaNumberBinaryOperation operation_type;

        constexpr explicit HashaBinaryOperatorVisitor(HashaNumberBinaryOperation op) :
                operation_type(op) {

        }

        constexpr HashaNumber operator()(auto A, auto B) const {

            switch (operation_type) {

                case HashaNumberBinaryOperation::Multiplication:
                    return A * B;
                case HashaNumberBinaryOperation::Divison:
                    return A / B;
                case HashaNumberBinaryOperation::Addition:
                    return A + B;
                case HashaNumberBinaryOperation::Subtraction:
                    return A - B;
            }
            return {};
        }
    };


    static constexpr HashaUnaryOperatorVisitor HashaNegOp{HashaNumberUnaryOperation::Negation};
    static constexpr HashaBinaryOperatorVisitor HashaMulOp{HashaNumberBinaryOperation::Multiplication};
    static constexpr HashaBinaryOperatorVisitor HashaDivOp{HashaNumberBinaryOperation::Divison};
    static constexpr HashaBinaryOperatorVisitor HashaAddOp{HashaNumberBinaryOperation::Addition};
    static constexpr HashaBinaryOperatorVisitor HashaSubOp{HashaNumberBinaryOperation::Subtraction};
}


#endif //HASHA_DEFAULTOPERATIONS_H

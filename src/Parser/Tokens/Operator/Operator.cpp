//
// Created by mythi on 26/08/22.
//
#include "Operator.h"

hasha::Operator::Operator(std::string op) noexcept: m_op(std::move(op)) {

}

const std::string &hasha::Operator::get_op() const noexcept {

    return m_op;
}

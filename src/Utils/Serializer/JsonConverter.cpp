//
// Created by mythi on 02/10/22.
//

#include "JsonConverter.h"

namespace hasha {
  nlohmann::ordered_json JsonConverter::operator()(const BoxedNormalType &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"type", obj->type()}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedGenericType &obj) const noexcept {

    auto type = std::visit(JsonConverter{}, obj->type());
    auto generics = nlohmann::ordered_json::array();
    for (const auto &generic: obj->generics_list()) {
      generics.push_back(std::visit(JsonConverter{}, generic));
    }
    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"type", type}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedIdentifier &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"identifier", obj->identifier()}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedType &obj) const noexcept {

    return std::visit(JsonConverter{}, obj);
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedDeclaration &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"assignment_expression", this->operator()(obj->assignment_expression())},
      {"span", obj->span().to_json()},
      {"name", this->operator()(obj->name())},
      {"type", std::visit(JsonConverter{}, obj->type())}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedExpression &obj) const noexcept {

    auto arr = nlohmann::ordered_json::array();
    for (const auto &token: obj->expression()) {
      arr.push_back(std::visit(JsonConverter{}, token));
    }
    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"expression", arr}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedLiteral &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"literal_type", magic_enum::enum_name(obj->type())},
      {"literal", obj->literal()}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedOperator &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"operator_type", magic_enum::enum_name(obj->type())},
      {"operation", obj->operation()}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedFunctionCall &obj) const noexcept {

    auto arguments = nlohmann::ordered_json::array();
    for (const auto &expression: obj->arguments()) {
      arguments.push_back(operator()(expression));
    }
    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"callee", obj->callee()},
      {"arguments", arguments}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedBlock &obj) const noexcept {

    auto tokens = nlohmann::ordered_json::array();
    for (const auto &token: obj->tokens()) {
      tokens.push_back(std::visit(JsonConverter{}, token));
    }


    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"tokens", tokens}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedAssignment &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedFunction &obj) const noexcept {

    auto parameters = nlohmann::ordered_json::array();
    int param_no = 1;
    for (const auto &param: obj->parameters()) {

      parameters.push_back(
        {fmt::format("arg_{}", param_no++), operator()(param)}
      );
    }
    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"name", operator()(obj->name())},
      {"parameters", parameters},
      {"return_type", operator()(obj->return_type())},
      {"block", operator()(obj->block())}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedParameter &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"type", operator()(obj->type())},
      {"name", operator()(obj->name())},
    };
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedIfStatement &obj) const noexcept {

    auto condition = nlohmann::ordered_json::array();
    for (const auto &token: obj->condition()->expression()) {
      condition.push_back(std::visit(JsonConverter{}, token));
    }

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"condition", condition},
      {"block", operator()(obj->block())}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedElifStatement &obj) const noexcept {

    auto condition = nlohmann::ordered_json::array();
    for (const auto &token: obj->condition()->expression()) {
      condition.push_back(std::visit(JsonConverter{}, token));
    }

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"condition", condition},
      {"block", operator()(obj->block())}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedElseStatement &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"block", operator()(obj->block())}};
  }

  nlohmann::ordered_json JsonConverter::operator()(const BoxedReturnToken &obj) const noexcept {

    return {
      {"token_type", obj->token_type()},
      {"span", obj->span().to_json()},
      {"expression", operator()(obj->expression())}};
  }
}// namespace hasha
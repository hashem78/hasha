//
// Created by mythi on 21/09/22.
//

#include "TypeChecker.h"
#include "Overload.h"
#include "Function.h"
#include "Type/NormalType.h"
#include "Type/GenericType.h"
#include "Identifier.h"
#include "Literal.h"
#include "Type/TypeComparer.h"
#include "Type/TypeToStringBuilder.h"
#include "Parameter.h"

namespace hasha {

    TypeChecker::TypeChecker(
            BoxedType type,
            Scope::Ptr scope
    ) :
            scope(std::move(scope)),
            type(std::move(type)) {
    }

    ErrorOr<void> TypeChecker::check_declaration(const BoxedDeclaration &declaration) {

        TRY(check_expression(declaration->assignment_expression()));

        return {};
    }

    ErrorOr<void> TypeChecker::check_expression(
            const BoxedExpression &expression
    ) {

        for (const auto &token: expression->expression()) {
            TRY(
                    std::visit(
                            Overload{
                                    [](auto) -> ErrorOr<void> { return {}; },
                                    [this](const BoxedLiteral &literal) -> ErrorOr<void> {
                                        TRY(check_literal(literal));
                                        return {};
                                    },
                                    [this](const BoxedFunctionCall &function_call) -> ErrorOr<void> {
                                        TRY(check_function_call(function_call));
                                        return {};
                                    },
                                    [this](const BoxedIdentifier &identifier) -> ErrorOr<void> {
                                        TRY(check_identifier(identifier));
                                        return {};
                                    }
                            },
                            token
                    )
            );
        }
        return {};
    }

    ErrorOr<void> TypeChecker::check_identifier(const BoxedIdentifier &identifier) {

        if (auto declaration = scope->get_declaration(identifier->identifier())) {


            if (!std::visit(TypeComparer{}, declaration->type(), type))
                return fmt::format(
                        "Identifier {} is not of type {} on line: {}, col: {}",
                        identifier->identifier(),
                        std::visit(TypeToStringBuilder{}, type),
                        identifier->span().line,
                        identifier->span().col
                );
        } else if (auto parameter = scope->get_parameter(identifier->identifier())) {
            if (!std::visit(TypeComparer{}, parameter->type(), type))
                return fmt::format(
                        "Parameter {} is not of type {} on line: {}, col: {}",
                        identifier->identifier(),
                        std::visit(TypeToStringBuilder{}, type),
                        identifier->span().line,
                        identifier->span().col
                );
        } else {
            return fmt::format(
                    "Failed to typecheck identifier {} on line : {}, col: {}",
                    identifier->identifier(),
                    identifier->span().line,
                    identifier->span().col
            );
        }
        return {};
    }

    ErrorOr<void> TypeChecker::check_literal(
            const BoxedLiteral &literal
    ) {

        bool failed = false;

        auto helper = [this](const std::string &str_tp) {
            return !std::visit(
                    Overload{
                            [&](const BoxedNormalType &tp) { return tp->type() == str_tp; },
                            [](auto) { return false; }
                    }, type
            );
        };
        std::string fail_type;
        switch (literal->type()) {

            case LiteralType::Integer:
                failed = helper("int");
                fail_type = "int";
                break;
            case LiteralType::Float:
                failed = helper("float");
                fail_type = "float";
                break;
            case LiteralType::String:
                failed = helper("string");
                fail_type = "string";
                break;
            case LiteralType::Boolean:
                failed = helper("bool");
                fail_type = "bool";
                break;
        }
        if (failed) {
            return fmt::format(
                    "Unexpected literal {} of type {} instead of type {} on line: {}, col: {}",
                    literal->literal(),
                    fail_type,
                    std::visit(TypeToStringBuilder{}, type),
                    literal->span().line,
                    literal->span().col
            );
        }
        return {};
    }

    ErrorOr<void> TypeChecker::check_function_call(const BoxedFunctionCall &function_call) {

        auto span = fmt::format("on line: {}, col: {}", function_call->span().line, function_call->span().col);
        auto function = scope->get_function(function_call->callee());
        if (function != nullptr) {
            if (!std::visit(TypeComparer{}, function->return_type(), type)) {
                return fmt::format(
                        "Return type of function {} is {} expected {} {}",
                        function->name()->identifier(),
                        std::visit(TypeToStringBuilder{}, function->return_type()),
                        std::visit(TypeToStringBuilder{}, type),
                        span
                );
            }

            // TODO: Use ranges here
            int i = 0;
            const auto &parameters = function->parameters();
            for (const auto &token: function_call->arguments()) {
                auto checker = TypeChecker{parameters[i++]->type(), scope};
                TRY(checker.check_expression(token));
            }
        } else {
            return fmt::format(
                    "Failed to typecheck call to {} on line: {}, col: {}",
                    function_call->callee(),
                    function_call->span().line,
                    function_call->span().col
            );
        }

        return {};
    }


} // hasha
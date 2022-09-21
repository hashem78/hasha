//
// Created by mythi on 21/09/22.
//

#include "TypeChecker.h"

namespace hasha {

    TypeChecker::TypeChecker(
            const Type &type,
            const Scope &scope
    ) : scope(scope),
        types() {

        types.push(type);
    }

    ErrorOr<void> TypeChecker::check_declaration(const Declaration &declaration) {

        TRY(check_expression(declaration.assignment_expression()));

        return {};
    }

    ErrorOr<void> TypeChecker::check_expression(
            const Expression &expression
    ) {

        for (const auto &token: expression.expression_tokens()) {
            if (auto literal = dynamic_cast<Literal *>(token.get())) {

                TRY(check_literal(*literal));

            } else if (auto function_call = dynamic_cast<FunctionCall *>(token.get())) {

                TRY(check_function_call(*function_call));
            }
        }
        return {};
    }

    ErrorOr<void> TypeChecker::check_literal(
            const Literal &literal
    ) {

        if (literal.type() != current_type()) {
            return fmt::format(
                    "Type of literal {} is not {} on line: {}, col: {}",
                    literal.get_literal(),
                    current_type().get_type(),
                    literal.span().line,
                    literal.span().col
            );
        }
        return {};
    }

    ErrorOr<void> TypeChecker::check_function_call(const FunctionCall &function_call) {

        const auto &function = *scope.get_function(function_call.get_callee());
        if (function.return_type() != current_type()) {
            return fmt::format(
                    "Return type of function {} is not {} on line: {}, col: {}",
                    function.name().get(),
                    current_type().get_type(),
                    function_call.span().line,
                    function_call.span().col
            );
        }
        auto span = fmt::format("on line: {}, col: {}", function_call.span().line, function_call.span().col);
        auto difference = std::abs(function.number_of_parameters() - function_call.get_number_of_args());

        if (function.number_of_parameters() > function_call.get_number_of_args()) {

            if (difference == 1) {
                return fmt::format(
                        "Call to {} is missing a required argument {}",
                        function_call.get_callee(),
                        span
                );
            } else {
                return fmt::format(
                        "Call to {} is missing {} required arguments {}",
                        function_call.get_callee(),
                        difference,
                        span
                );
            }
        }
        if (function.number_of_parameters() < function_call.get_number_of_args()) {

            if (difference == 1) {
                return fmt::format(
                        "Call to {} has an extra argument {}",
                        function_call.get_callee(),
                        span
                );
            } else {
                return fmt::format(
                        "Call to {} has {} extra arguments {}",
                        function_call.get_callee(),
                        difference,
                        span
                );
            }
        }
        if (function.number_of_parameters() == function_call.get_number_of_args()) {

            // TODO: Use ranges here
            int i = 0;
            const auto &parameters = function.parameters();
            for (const auto &token: function_call.get_arguments()) {
                set_type(parameters[i++]->type());
                TRY(check_expression(*token));
                restore_type();
            }
        }


        return {};
    }

    const Type &TypeChecker::current_type() const {

        return types.top();
    }

    void TypeChecker::set_type(const Type &type) {

        types.push(type);
    }

    void TypeChecker::restore_type() {

        types.pop();
    }

} // hasha
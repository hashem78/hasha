//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_PARSER_H
#define HASHA_PARSER_H


#include "Lexeme.h"
#include "Lexer.h"
#include "Pattern.h"
#include "ErrorOr.h"
#include "Context.h"
#include "Scope.h"
#include "ScopeTree.h"

#include "Identifier.h"
#include "Type/Type.h"
#include "Type/GenericType.h"
#include "Type/NormalType.h"
#include "Declaration.h"
#include "Expression.h"
#include "Literal.h"
#include "Operator.h"
#include "FunctionCall.h"
#include "Block.h"
#include "Assignment.h"
#include "Block.h"
#include "Function.h"
#include "Parameter.h"
#include "Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "ReturnToken.h"


namespace hasha {

    class Parser {
        ScopeTree::Ptr scope_tree;
        Lexer lexer;
        std::vector<Lexeme> lexemes;
        int cursor;

        ErrorOr<Box<Identifier>> identifier(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedNormalType> type(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedGenericType> generic_type(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedDeclaration> declaration(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedExpression>
        parse_expression(
                const Scope::Ptr &lexeme
        );

        ErrorOr<BoxedFunctionCall>
        function_call(
                const Scope::Ptr &scope,
                bool check_scope
        ) noexcept;

        ErrorOr<BoxedExpressionList>
        parse_multiple(
                const Scope::Ptr &scope,
                const Lexeme &left,
                const Lexeme &right,
                const Lexeme &separator = COMMA
        );

        ErrorOr<BoxedLiteral> literal(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedBlock> block(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedParameter> parameter(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedFunction> function(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedAssignment> assignment(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedIfStatement> if_statement(const Scope::Ptr &scope) noexcept;

        ErrorOr<BoxedElifStatement> elif_statement(
                const Token &previous_token,
                const Scope::Ptr &scope
        ) noexcept;

        ErrorOr<BoxedElseStatement> else_statement(
                const Token &previous_token,
                const Scope::Ptr &scope
        ) noexcept;

        ErrorOr<BoxedReturnToken> return_token(const Scope::Ptr &scope) noexcept;

        ContextStack context_stack;

        Context current_context();

        void set_context(Context context);

        void restore_context();

        [[nodiscard]]
        Lexeme peek(std::size_t k = 0) const noexcept;

        [[nodiscard]]
        bool done(int k = 0) const noexcept;

        Lexeme advance(int k = 1) noexcept;

        [[nodiscard]]
        inline bool match(const Lexeme &match, int start = 0) const noexcept;

        [[nodiscard]]
        inline bool match(const LexemeType &match, int start = 0) const noexcept;

        [[nodiscard]]
        bool match(const Patterns::Pattern &matchers) const noexcept;

    public:

        explicit Parser(std::string file_name, ScopeTree::Ptr scope_tree);

        ErrorOr<std::pair<Scope::Ptr, BoxedBlock>> parse();

    };

} // hasha

#endif //HASHA_PARSER_H

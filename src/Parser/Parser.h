//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_PARSER_H
#define HASHA_PARSER_H


#include <stack>

#include "Context.h"
#include "ErrorOr.h"
#include "Lexeme.h"
#include "Lexer.h"
#include "Pattern.h"
#include "Scope.h"
#include "ScopeTree.h"

#include "Assignment.h"
#include "Block.h"
#include "Declaration.h"
#include "Expression.h"
#include "Function.h"
#include "FunctionCall.h"
#include "Identifier.h"
#include "Literal.h"
#include "Operator.h"
#include "Parameter.h"
#include "ReturnToken.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "Statement/IfStatement.h"
#include "Type/GenericType.h"
#include "Type/NormalType.h"
#include "Type/Type.h"


namespace hasha {

  class Parser {
    using ContextStack = std::stack<Context>;
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
      const Scope::Ptr &lexeme,
      const Patterns::Pattern &delimiters = {SEMICOLON}
    );

    ErrorOr<BoxedFunctionCall> function_call(const Scope::Ptr &scope) noexcept;

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

    [[nodiscard]] Lexeme peek(std::size_t k = 0) const noexcept;

    [[nodiscard]] bool done(int k = 0) const noexcept;

    Lexeme advance(int k = 1) noexcept;

    [[nodiscard]] inline bool match(const Lexeme &match, int start = 0) const noexcept;

    [[nodiscard]] inline bool match(const LexemeType &match, int start = 0) const noexcept;

    [[nodiscard]] bool match(const Patterns::Pattern &matchers) const noexcept;

    [[nodiscard]] bool match_any(const Patterns::Pattern &matchers) const noexcept;

   public:
    explicit Parser(std::string file_name, ScopeTree::Ptr scope_tree);

    ErrorOr<std::pair<Scope::Ptr, BoxedBlock>> parse();
  };

}// namespace hasha

#endif//HASHA_PARSER_H

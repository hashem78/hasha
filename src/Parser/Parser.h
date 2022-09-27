//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_PARSER_H
#define HASHA_PARSER_H


#include "Tokens/Token.h"
#include "Lexeme.h"
#include "Identifier.h"
#include "Lexer.h"
#include "Parameter.h"
#include "Function.h"
#include "Tokens/Literal/Literal.h"
#include "Tokens/Declaration.h"
#include "Tokens/Operator/BinaryOperator.h"
#include "Pattern.h"
#include "Literal/StringLiteral.h"
#include "Literal/IntegerLiteral.h"
#include "Literal/FloatingPointLiteral.h"
#include "Literal/BooleanLiteral.h"
#include "Operator/UnaryOperator.h"
#include "Operator/BinaryOperator.h"
#include "FunctionCall.h"
#include "ErrorOr.h"
#include "Tokens/Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "Type/Type.h"
#include "Context.h"
#include "Tokens/Expression/Expression.h"
#include "Expression/ReturnExpression.h"
#include "Scope.h"
#include "ScopeTree.h"
#include "Type/GenericType.h"

namespace hasha {

    class Parser {
        ScopeTree::Ptr scope_tree;
        Lexer lexer;
        LexemeList lexemes;
        int cursor;

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
        bool match(const Patterns::Pattern &matchers, int start = 0) const noexcept;

        [[nodiscard]]
        bool match_any(const Patterns::Pattern &matchers) const noexcept;



        [[nodiscard]]
        ErrorOr<Identifier::Ptr>
        identifier(
                Scope &scope,
                bool check_for_redefiniton = false,
                bool register_to_scope = true
        ) noexcept;

        ErrorOr<Type::Ptr> type(Scope &scope) noexcept;

        ErrorOr<Parameter::Ptr> parameter(Scope &scope);

        ErrorOr<Declaration::Ptr> declaration(Scope &scope);

        ErrorOr<FunctionCall::Ptr> function_call(Scope &scope, bool check_scope = false);

        ErrorOr<Expression::Ptr> parse_expression(Scope &scope, const Lexeme &delimiter = SEMICOLON);

        ErrorOr<ExpressionList>
        parse_multiple(Scope &scope, const Lexeme &left, const Lexeme &right, const Lexeme &separator = COMMA);

        ErrorOr<Literal::Ptr> literal(Scope &scope);

        ErrorOr<Block::Ptr> block(Scope &scope) noexcept;

        ErrorOr<Function::Ptr> function(Scope &scope);

        ErrorOr<IfStatement::Ptr> if_statement(Scope &scope);

        ErrorOr<ElifStatement::Ptr> elif_statement(Scope &scope);

        ErrorOr<ElseStatement::Ptr> else_statement(Scope &scope);

        ErrorOr<Expression::Ptr> return_expression(Scope &scope);

        ErrorOr<Assignment::Ptr> assignment(Scope &scope);


        template<class T>
        std::optional<const T *> last_of(const TokenList &tkns) {

            for (auto it = tkns.rbegin(); it != tkns.rend(); it++) {

                auto cast = dynamic_cast<T *>(it->get());
                if (cast)
                    return cast;
            }
            return {};
        }

        template<class T>
        bool is_previous_of(const TokenList &tkns) {

            if (tkns.empty())
                return false;

            auto cast = dynamic_cast<T *>(tkns.back().get());

            if (cast)
                return true;

            return false;
        }

    public:

        explicit Parser(std::string file_name, ScopeTree::Ptr scope_tree);

        ErrorOr<Block::Ptr> parse();

    };

} // hasha

#endif //HASHA_PARSER_H

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
#include "Tokens/Operator.h"
#include "Pattern.h"
#include "Literal/StringLiteral.h"
#include "Literal/NumericLiteral.h"
#include "Literal/BooleanLiteral.h"
#include "Operator.h"
#include "FunctionCall.h"
#include "ErrorOr.h"
#include "Tokens/Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "Type/Type.h"
#include "Type/ArrayType.h"
#include "Context.h"
#include "Tokens/Expression/Expression.h"
#include "Assignment/ArrayAssignment.h"
#include "Expression/ReturnExpression.h"
#include "Scope.h"
#include "ScopeTree.h"
#include "Assignment/InlineAssignment.h"
#include "Assignment/ArrayInlineAssignment.h"

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

        template<size_t S>
        [[nodiscard]]
        inline bool match_any(const Patterns::Pattern<S> &matchers) const noexcept {

            for (std::size_t i = 0; i < matchers.size(); ++i) {

                auto matched = std::visit(
                        Patterns::PatternVisitor{
                                [&, this](const Lexeme &lexeme) -> bool {
                                    return peek() == lexeme;
                                },
                                [&, this](const LexemeType &lexeme_type) -> bool {
                                    return peek().type() == lexeme_type;
                                },
                                [&, this](const Patterns::PatternFunctor &pattern_functor) -> bool {
                                    return pattern_functor(lexemes, cursor).matched;
                                }
                        }, matchers[i]
                );
                if (matched)
                    return true;

            }
            return false;
        }


        template<size_t S>
        [[nodiscard]]
        inline bool match(const Patterns::Pattern<S> &matchers, int start = 0) const noexcept {

            int lookahed = 0;
            for (std::size_t i = start; i < matchers.size(); ++i) {

                auto not_matched = std::visit(
                        Patterns::PatternVisitor{
                                [&, this](const Lexeme &lexeme) -> bool {
                                    return peek(i + lookahed) != lexeme;
                                },
                                [&, this](const LexemeType &lexeme_type) -> bool {
                                    return peek(i + lookahed).type() != lexeme_type;
                                },
                                [&, this](const Patterns::PatternFunctor &pattern_functor) -> bool {
                                    auto result = pattern_functor(lexemes, cursor);
                                    if (result.matched) {
                                        lookahed += result.cursor;
                                        return false;
                                    }
                                    return true;
                                }
                        }, matchers[i]
                );
                if (not_matched)
                    return false;

            }
            return true;
        }

        [[nodiscard]]
        ErrorOr<Identifier::Ptr>
        identifier(Scope &scope, bool check_scope = false, bool register_to_scope = true) noexcept;

        ErrorOr<Type::Ptr> type() noexcept;

        ErrorOr<Parameter::Ptr> parameter(Scope &scope);

        ErrorOr<Declaration::Ptr> declaration(Scope &scope);

        ErrorOr<Declaration::Ptr> declaration_with_assignment(Scope &scope);

        ErrorOr<Assignment::Ptr> inline_assignment(Scope &scope);

        ErrorOr<FunctionCall::Ptr> function_call(Scope &scope, bool check_scope = false);

        ErrorOr<Expression::Ptr> parse_expression(Scope &scope, const Lexeme &delimiter = SEMICOLON);

        ErrorOr<Assignment::Ptr> assignment(Scope &scope);

        ErrorOr<ExpressionList>
        parse_multiple(Scope &scope, const Lexeme &left, const Lexeme &right, const Lexeme &separator = COMMA);

        ErrorOr<Literal::Ptr> literal();

        ErrorOr<Block::Ptr> block(Scope &scope) noexcept;

        ErrorOr<Function::Ptr> function(Scope &scope);

        ErrorOr<IfStatement::Ptr> if_statement(Scope &scope);

        ErrorOr<ElifStatement::Ptr> elif_statement(Scope &scope);

        ErrorOr<ElseStatement::Ptr> else_statement(Scope &scope);

        ErrorOr<Expression::Ptr> return_expression(Scope &scope);

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

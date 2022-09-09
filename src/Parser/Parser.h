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

namespace hasha {

    class Parser {
        Lexer lexer;
        LexemeList lexemes;
        int cursor;

        TokenList tokens;

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
        ErrorOr<Identifier::Ptr> identifier() noexcept;

        ErrorOr<Type::Ptr> type() noexcept;

        ErrorOr<Parameter::Ptr> parameter();

        ErrorOr<Declaration::Ptr> declaration();

        ErrorOr<FunctionCall::Ptr> function_call();

        ErrorOr<Expression::Ptr> parse_expression(const Lexeme &delimiter = SEMICOLON);

        ErrorOr<Assignment::Ptr> assignment();

        ErrorOr<ExpressionList>
        parse_multiple(const Lexeme &left, const Lexeme &right, const Lexeme &separator = COMMA);

        ErrorOr<Literal::Ptr> literal();

        ErrorOr<Block::Ptr> block() noexcept;

        ErrorOr<Function::Ptr> function();

        ErrorOr<IfStatement::Ptr> if_statement();

        ErrorOr<ElifStatement::Ptr> elif_statement();

        ErrorOr<ElseStatement::Ptr> else_statement();

        ErrorOr<Expression::Ptr> return_expression();

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
        bool is_previous_of() {

            if (tokens.empty())
                return false;

            auto cast = dynamic_cast<T *>(tokens.back().get());

            if (cast)
                return true;

            return false;
        }

    public:
        [[nodiscard]]
        const TokenList &get_tokens() const noexcept;

        explicit Parser(std::string file_name);

        ErrorOr<Block::Ptr> parse();

    };

} // hasha

#endif //HASHA_PARSER_H

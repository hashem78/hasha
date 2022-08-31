//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_PARSER_H
#define HASHA_PARSER_H

#include <optional>
#include <variant>
#include <deque>
#include <stack>
#include <utility>


#include "magic_enum.hpp"

#include "Constants.h"
#include "Tokens/Token.h"
#include "Lexeme.h"
#include "Identifier.h"
#include "Lexer.h"
#include "Parameter.h"
#include "Function.h"
#include "Tokens/Literal/Literal.h"
#include "Tokens/Declaration.h"
#include "Tokens/Operator/Operator.h"
#include "Pattern.h"
#include "Literal/StringLiteral.h"
#include "Literal/NumericLiteral.h"
#include "Literal/BooleanLiteral.h"
#include "Operator/BooleanOperator.h"
#include "Operator/NumericOperator.h"
#include "FunctionCall.h"
#include "ErrorOr.h"
#include "Tokens/Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "Type/Type.h"
#include "Type/ArrayType.h"

namespace hasha {

    class Parser {
        Lexer lexer;
        LexemeList lexemes;
        int cursor;

        TokenList tokens;

        [[nodiscard]]
        Lexeme peek(std::size_t k = 0) const noexcept;

        [[nodiscard]]
        bool done() const noexcept;

        Lexeme advance() noexcept;

        [[nodiscard]]
        inline bool match(const Lexeme &match) const noexcept;

        [[nodiscard]]
        inline bool match(const LexemeType &match) const noexcept;

        template<size_t S>
        [[nodiscard]]
        inline bool match(const Patterns::Pattern<S> &matchers) const noexcept {

            int lookahed = 0;
            for (std::size_t i = 0; i < matchers.size(); ++i) {

                auto should_return = std::visit(
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
                if (should_return)
                    return false;

            }
            return true;
        }

        [[nodiscard]]
        ErrorOr<Identifier> identifier() noexcept;

        ErrorOr<Type::Ptr> type() noexcept;

        ErrorOr<Parameter::Ptr> parameter();

        ErrorOr<Declaration::Ptr> variable_declaration();

        ErrorOr<Declaration::Ptr> array_declaration_and_assignemnt();


        ErrorOr<TokenListPtr> parse_expression(const Lexeme &delimiter = SEMICOLON);

        ErrorOr<Declaration::Ptr> variable_declaration_and_assignment();

        ErrorOr<Assignment::Ptr> variable_assignment();

        ErrorOr<TokenListPtr> parse_multiple(const Lexeme &left, const Lexeme &right, const Lexeme &separator = COMMA);


        ErrorOr<Block::Ptr> block() noexcept;

        ErrorOr<Function::Ptr> function();

        ErrorOr<IfStatement::Ptr> if_statement();

        ErrorOr<ElifStatement::Ptr> elif_statement();

        ErrorOr<ElseStatement::Ptr> else_statement();

        template<class T>
        std::optional<const T *> last_of(const TokenList *tkns) {

            for (auto it = tkns->rbegin(); it != tkns->rend(); it++) {

                auto cast = dynamic_cast<T *>(it->get());
                if (cast)
                    return cast;
            }
            return {};
        }

        template<class T>
        bool is_previous_of(const TokenList *tkns) {

            if (tkns->empty())
                return false;

            auto cast = dynamic_cast<T *>(tkns->back().get());

            if (cast)
                return true;

            return false;
        }

    public:
        [[nodiscard]]
        const TokenList &get_tokens() const noexcept;

        explicit Parser(std::string file_name);

        [[nodiscard]]
        const LexemeList &get_lexemes() const noexcept;

        void parse();

    };

} // hasha

#endif //HASHA_PARSER_H

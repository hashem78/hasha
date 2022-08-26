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

                const auto &matcher = matchers[i];

                if (holds_alternative<LexemeType>(matcher)) {
                    auto type = get<LexemeType>(matcher);
                    if (peek(i + lookahed).get_type() != type)
                        return false;
                } else if (holds_alternative<Lexeme>(matcher)) {
                    auto lexeme = get<Lexeme>(matcher);
                    if (peek(i + lookahed) != lexeme)
                        return false;
                } else {

                    auto functor = get<Patterns::PatternFunctor>(matcher);
                    Patterns::FunctorResult result = functor(lexemes, cursor);
                    if (result.state == Patterns::FunctorState::MATCH) {
                        lookahed += result.cursor;
                    } else {
                        return false;
                    }
                }
            }
            return true;
        }

        [[nodiscard]]
        ErrorOr<Identifier> identifier() noexcept;

        ErrorOr<Parameter::Ptr> parameter();

        ErrorOr<Declaration::Ptr> variable_declaration();

        ErrorOr<Declaration::Ptr> array_declaration();

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
        std::optional<const T*> last_of(const TokenList* tkns) {

            for (auto it = tkns->rbegin(); it != tkns->rend(); it++) {

                auto cast = dynamic_cast<T*>(it->get());
                if(cast)
                    return cast;
            }
            return {};
        }
        template<class T>
        bool is_previous_of(const TokenList* tkns) {

            if(tkns->empty())
               return false;

            auto cast = dynamic_cast<T*>(tkns->back().get());

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

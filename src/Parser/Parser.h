//
// Created by mythi on 21/07/22.
//

#ifndef HASHA_PARSER_H
#define HASHA_PARSER_H

#include <optional>

#include "Lexeme.h"
#include "Lexer.h"
#include "Function.h"
#include "VariableAssignment.h"
#include "Tokens/Token.h"
#include "Expressions/ArrayExpression.h"
#include "Declarations/ArrayDeclaration.h"

namespace hasha {

    class Parser {
        Lexer lexer;
        LexemeList lexemes;
        int cursor;

        TokenList tokens;

        void add_token(TokenPtr ptr);

        [[nodiscard]]
        Lexeme peek(int k = 0) const;

        [[nodiscard]]
        bool exists_from(const Lexeme &lexeme, int from) const;

        [[nodiscard]]
        bool expect(const LexemeType &);

        [[nodiscard]]
        bool expect(const Lexeme &);

        [[nodiscard]]
        bool done() const;

        bool parse_function();

        void next();

    public:
        [[nodiscard]]
        const TokenList &get_tokens() const;

        explicit Parser(std::string file_name);

        [[nodiscard]]
        const LexemeList &get_lexemes() const;

        void parse();


        ParameterListPtr parse_parameters();

        Block::BlockPtr parse_block();

        VariableDeclaration::VariableDeclarationPtr parse_variable_declaration();


        VariableAssignment::VariableAssignmentPtr parse_variable_assignment();

        ArrayDeclaration::ArrayDeclarationPtr parse_array_declaration_of_type(std::string type);

        std::shared_ptr<ArrayExpression> parse_array();

        bool is_array_decl() const;
    };

} // hasha

#endif //HASHA_PARSER_H

//
// Created by mythi on 03/09/22.
//

#ifndef HASHA_INTERPRETER_H
#define HASHA_INTERPRETER_H

#include "ScopeTree.h"
#include "Block.h"
#include "Function.h"
#include "Declaration.h"
#include "Statement/IfStatement.h"
#include "Statement/ElifStatement.h"
#include "Statement/ElseStatement.h"
#include "SymbolTree.h"
#include "Literal/Literal.h"
#include "ExpressionResult.h"

namespace hasha::interpeter {

    class Interpreter {
        Block::Ptr global_block;
        ScopeTree::Ptr scope_tree;
        SymbolTree::Ptr symbol_tree;

    public:
        explicit Interpreter(Block::Ptr block, ScopeTree::Ptr scope_tree);

        ErrorOr<void> interpret_if(const IfStatement &if_statement, SymbolTable &table);

        ErrorOr<void> interpret_elif(const ElifStatement &elif_statement, SymbolTable &table);

        ErrorOr<void> interpret_else(const ElseStatement &else_statement, SymbolTable &table);

        ErrorOr<void> interpret_assignment(const Assignment& assignment,SymbolTable &table);

        ErrorOr<ExpressionResult> interpret_expression(const Expression &expression, SymbolTable &table);

        ErrorOr<void> interpret_declaration(const Declaration &declaration, SymbolTable &table);

        ErrorOr<void> interpret_function(const Function &function, SymbolTable &table);

        ErrorOr<void> interpret_block(const Block &block, SymbolTable &table);


        ErrorOr<void> interpret();
    };

} // hasha

#endif //HASHA_INTERPRETER_H

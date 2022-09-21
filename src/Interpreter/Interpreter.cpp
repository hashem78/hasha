//
// Created by mythi on 03/09/22.
//

#include <stack>
#include "Interpreter.h"

#include "Operator.h"

#include "FunctionCall.h"
#include "TypeChecker.h"

namespace hasha {
    Interpreter::Interpreter(
            Block::Ptr block,
            ScopeTree::Ptr scope_tree
    ) :
            global_block(std::move(block)),
            scope_tree(std::move(scope_tree)),
            symbol_tree(std::move(SymbolTree::create())) {
    }

    ErrorOr<void> Interpreter::interpret_if(const IfStatement &if_statement, SymbolTable &table) {

        return {};
    }

    ErrorOr<void> Interpreter::interpret_elif(const ElifStatement &elif_statement, SymbolTable &table) {

        return {};
    }

    ErrorOr<void> Interpreter::interpret_else(const ElseStatement &else_statement, SymbolTable &table) {

        return {};
    }

    ErrorOr<void> Interpreter::interpret_declaration(const Declaration &declaration, SymbolTable &table) {

        const auto &scope = *scope_tree->get_by_id(declaration.scope_id());
        TypeChecker type_checker(declaration.type(), scope);

        TRY(type_checker.check_declaration(declaration));

        return {};
    }

    ErrorOr<void> Interpreter::interpret_function(const Function &function, SymbolTable &table) {

        TRY(interpret_block(function.block(), table));

        return {};
    }

    ErrorOr<void> Interpreter::interpret_block(const Block &block, SymbolTable &table) {

        auto new_table = symbol_tree->create_table(table.id);

        for (const auto &block_token: block.get_tokens()) {
            if (auto decl = dynamic_cast<Declaration *>(block_token.get())) {
                TRY(interpret_declaration(*decl, new_table));
            } else if (auto if_st = dynamic_cast<IfStatement *>(block_token.get())) {
                TRY(interpret_if(*if_st, new_table));
            } else if (auto elif_st = dynamic_cast<ElifStatement *>(block_token.get())) {
                TRY(interpret_elif(*elif_st, new_table));
            } else if (auto else_st = dynamic_cast<ElseStatement *>(block_token.get())) {
                TRY(interpret_else(*else_st, new_table));
            }
        }
        return {};
    }

    ErrorOr<void> Interpreter::interpret() {

        auto global_symbol_table = symbol_tree->create_table();
        for (const auto &block_token: global_block->get_tokens()) {
            if (auto fn = dynamic_cast<Function *>(block_token.get())) {
                TRY(interpret_function(*fn, global_symbol_table));
            }
        }

        return {};
    }

} // hasha
//
// Created by mythi on 02/10/22.
//

#include "Interpreter.h"
#include "Vistors/GlobalBlockVisitor.h"

namespace hasha {
    Interpreter::Interpreter(
            BoxedBlock block,
            ScopeTree::Ptr scope_tree,
            Scope::Ptr global_scope
    ) noexcept:
            global_block(std::move(block)),
            scope_tree(std::move(scope_tree)),
            global_scope(std::move(global_scope)),
            symbol_table_tree(SymbolTableTree::create()) {


    }

    ErrorOr<void> Interpreter::interpret() {

        auto global_symbol_table = symbol_table_tree->global_symbol_table();

        for (const auto &token: global_block->tokens()) {

            TRY(
                    std::visit(
                            GlobalBlockVisitor{
                                    global_scope,
                                    global_symbol_table,
                                    scope_tree,
                                    symbol_table_tree
                            },
                            token
                    )
            );
        }
        return {};
    }
} // hasha
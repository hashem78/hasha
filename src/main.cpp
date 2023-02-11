#include "ErrorOr.h"
#include "Interpreter.h"
#include "Parser/Parser.h"
#include "Scope.h"
#include "Serializer/Serializer.h"

hasha::ErrorOr<void> hasha_main() {

  auto scope_tree = hasha::ScopeTree::create();
  auto parser = hasha::Parser{"sample.hasha", scope_tree};
  auto [global_scope, global_block] = TRY(parser.parse());
  auto serializer = hasha::Serializer{global_block, "parser_output.json"sv};
  serializer.serialize();
  serializer.dump();
  auto interpreter = hasha::Interpreter(global_block, scope_tree, global_scope);
  TRY(interpreter.interpret());
  return {};
}

int main() {

  auto res = hasha_main();

  if (res.is_error()) {
    fmt::print("{}\n", res.error());
    return 1;
  }

  return 0;
}

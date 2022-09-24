#include "Parser/Parser.h"
#include "Interpreter/Interpreter.h"
#include "ErrorOr.h"

hasha::ErrorOr<void> hasha_main() {
    using namespace hasha;
    auto scope_tree = ScopeTree::create();
    auto parser = Parser{"sample.hasha", scope_tree};

    auto interpreter = interpeter::Interpreter{TRY(parser.parse()), scope_tree};
    TRY(interpreter.interpret());

    return {};
}

int main() {

    auto res = hasha_main();

    if (res.is_error()) {
        fmt::print("{}", res.error());
        return 1;
    }

    return 0;
}

#include "Parser/Parser.h"
#include "Interpreter/Interpreter.h"
#include "ErrorOr.h"
#include "Scope.h"

hasha::ErrorOr<void> hasha_main() {


    auto parser = hasha::Parser{"sample.hasha", hasha::ScopeTree::create()};

    auto interpreter = hasha::Interpreter{TRY(parser.parse())};
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

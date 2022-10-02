#include "Parser/Parser.h"
#include "ErrorOr.h"
#include "Scope.h"
#include "Serializer/Serializer.h"

hasha::ErrorOr<void> hasha_main() {

    auto scope_tree = hasha::ScopeTree::create();
    auto parser = hasha::Parser{"sample.hasha", scope_tree};
    auto serializer = hasha::Serializer{TRY(parser.parse()), "parser_output.json"sv};
    serializer.serialize();
    serializer.dump();
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

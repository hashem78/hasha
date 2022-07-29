#include "Lexer.h"
#include "fmt/format.h"
#include "Parser/Parser.h"

int main() {

    hasha::Parser parser("sample.hasha");

    for (const auto &lexeme: parser.get_lexemes()) {
        fmt::print("{}\n", lexeme.to_string());
    }
    fmt::print("Starting Parser\n");

    parser.parse();

    for (const auto &token: parser.get_tokens()) {
        fmt::print("{}\n", token->to_string());
    }

    return 0;
}

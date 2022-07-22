cmake_minimum_required(VERSION 3.22)
project(hasha)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/fmt)
add_subdirectory(libs/json)
add_subdirectory(libs/magic_enum)

include_directories(src/Lexer src/Parser src/Parser/Tokens)
add_executable(hasha src/main.cpp src/Lexer/Lexer.cpp src/Lexer/Lexer.h src/Lexer/Lexeme.cpp src/Lexer/Lexeme.h src/Parser/Parser.cpp src/Parser/Parser.h src/Parser/Tokens/Token.cpp src/Parser/Tokens/Token.h src/Parser/Declarations/VariableDeclaration.cpp src/Parser/Declarations/VariableDeclaration.h src/Parser/Tokens/Block.cpp src/Parser/Tokens/Block.h src/Parser/Tokens/Function.cpp src/Parser/Tokens/Function.h src/Parser/ParserState.h src/Parser/Tokens/VariableAssignment.cpp src/Parser/Tokens/VariableAssignment.h src/Parser/Tokens/Expressions/Expression.cpp src/Parser/Tokens/Expressions/Expression.h src/Parser/Tokens/Expressions/ArrayExpression.cpp src/Parser/Tokens/Expressions/ArrayExpression.h src/Parser/Tokens/Expressions/LiteralExpression.cpp src/Parser/Tokens/Expressions/LiteralExpression.h src/Parser/Declarations/ArrayDeclaration.cpp src/Parser/Declarations/ArrayDeclaration.h)

target_link_libraries(hasha fmt::fmt nlohmann_json::nlohmann_json magic_enum::magic_enum)

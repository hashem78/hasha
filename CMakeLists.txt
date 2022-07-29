cmake_minimum_required(VERSION 3.22)
project(hasha)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/fmt)
add_subdirectory(libs/json)
add_subdirectory(libs/magic_enum)

include_directories(src/Lexer src/Parser src/Parser/Tokens)
add_executable(hasha
        src/main.cpp
        src/Lexer/Lexer.cpp
        src/Lexer/Lexer.h
        src/Lexer/Lexeme.cpp
        src/Lexer/Lexeme.h
        src/Parser/Parser.cpp
        src/Parser/Parser.h
        src/Parser/Tokens/Token.cpp
        src/Parser/Tokens/Token.h
        src/Parser/Tokens/Declaration.cpp
        src/Parser/Tokens/Declaration.h
        src/Parser/Tokens/Block.cpp
        src/Parser/Tokens/Block.h
        src/Parser/Tokens/Function.cpp
        src/Parser/Tokens/Function.h
        src/Parser/ParserState.h
        src/Parser/Tokens/Identifier.cpp
        src/Parser/Tokens/Identifier.h
        src/Parser/Tokens/Parameter.cpp
        src/Parser/Tokens/Parameter.h
        src/Parser/Tokens/Literal/Literal.h
        src/Parser/Tokens/Operator/Operator.h
        src/Parser/Tokens/Assignment.cpp
        src/Parser/Tokens/Assignment.h
        src/Parser/Pattern.h src/Parser/Tokens/Literal/StringLiteral.h src/Parser/Tokens/Literal/NumericLiteral.h src/Parser/Tokens/Literal/BooleanLiteral.h src/Parser/Tokens/Operator/BooleanOperator.cpp src/Parser/Tokens/Operator/BooleanOperator.h src/Parser/Tokens/Operator/NumericOperator.cpp src/Parser/Tokens/Operator/NumericOperator.h)

target_link_libraries(hasha fmt::fmt nlohmann_json::nlohmann_json magic_enum::magic_enum)

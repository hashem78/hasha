cmake_minimum_required(VERSION 3.22)
project(hasha)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/fmt)
add_subdirectory(libs/json)
add_subdirectory(libs/magic_enum)

include_directories(src/Lexer src/Parser src/Parser/Tokens src/Parser/Scope src/Interpreter src/Utils)
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
        src/Parser/Tokens/Identifier.cpp
        src/Parser/Tokens/Identifier.h
        src/Parser/Tokens/Parameter.cpp
        src/Parser/Tokens/Parameter.h
        src/Parser/Tokens/Literal/Literal.h
        src/Parser/Tokens/Operator.h
        src/Parser/Tokens/Assignment/ArrayAssignment.cpp
        src/Parser/Tokens/Assignment/ArrayAssignment.h
        src/Parser/Pattern.h src/Parser/Tokens/Literal/StringLiteral.h
        src/Parser/Tokens/Literal/NumericLiteral.h
        src/Parser/Tokens/Literal/BooleanLiteral.h
        src/Lexer/Constants.h
        src/Parser/Tokens/FunctionCall.cpp
        src/Parser/Tokens/FunctionCall.h
        src/Utils/ErrorOr.h
        src/Parser/Tokens/Operator.cpp
        src/Parser/Tokens/Literal/BooleanLiteral.cpp
        src/Parser/Tokens/Literal/Literal.cpp
        src/Parser/Tokens/Literal/NumericLiteral.cpp
        src/Parser/Tokens/Literal/StringLiteral.cpp
        src/Parser/Tokens/Statement/IfStatement.cpp
        src/Parser/Tokens/Statement/IfStatement.h
        src/Parser/Tokens/Statement/ElifStatement.cpp
        src/Parser/Tokens/Statement/ElifStatement.h src/Parser/Tokens/Statement/ElseStatement.cpp
        src/Parser/Tokens/Statement/ElseStatement.h src/Parser/Tokens/Type/Type.cpp
        src/Parser/Tokens/Type/Type.h src/Parser/Tokens/Type/ArrayType.cpp
        src/Parser/Tokens/Type/ArrayType.h src/Parser/Context.h src/Parser/Tokens/Expression/Expression.cpp
        src/Parser/Tokens/Expression/Expression.h src/Parser/Tokens/Assignment/Assignment.cpp
        src/Parser/Tokens/Assignment/Assignment.h src/Parser/Context.cpp
        src/Utils/Span.h src/Parser/Tokens/Expression/ReturnExpression.h src/Parser/Tokens/Expression/ReturnExpression.cpp
        src/Lexer/Analyzer.cpp
        src/Lexer/Analyzer.h src/Interpreter/Interpreter.cpp
        src/Interpreter/Interpreter.h src/Parser/Scope/Scope.cpp
        src/Parser/Scope/Scope.h
        src/Interpreter/Variable.h
        src/Interpreter/Variable.cpp src/Parser/Scope/GlobalScope.cpp src/Parser/Scope/GlobalScope.h)

target_link_libraries(hasha fmt::fmt nlohmann_json::nlohmann_json magic_enum::magic_enum)

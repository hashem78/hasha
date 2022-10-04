cmake_minimum_required(VERSION 3.22)
project(hasha)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/fmt)
add_subdirectory(libs/json)
add_subdirectory(libs/magic_enum)

include_directories(
        src/Lexer
        src/Parser
        src/Parser/Tokens
        src/Utils
        src/Scope
        src/Interpreter
)
add_executable(hasha
        src/main.cpp
        src/Lexer/Lexer.cpp
        src/Lexer/Lexer.h
        src/Lexer/Lexeme.cpp
        src/Lexer/Lexeme.h
        src/Lexer/Analyzer.cpp
        src/Lexer/Analyzer.h
        src/Lexer/LexerTypes.h
        src/Lexer/Constants.h
        src/Parser/Tokens/Token.h
        src/Parser/Tokens/TokenBase.cpp
        src/Parser/Tokens/TokenBase.h
        src/Parser/Parser.cpp
        src/Parser/Parser.h
        src/Parser/Pattern.h
        src/Parser/Context.h
        src/Parser/Context.cpp
        src/Scope/Scope.h
        src/Scope/ScopeTree.cpp
        src/Scope/ScopeTree.h
        src/Scope/Scope.cpp
        src/Utils/ErrorOr.h
        src/Utils/Span.h
        src/Utils/Box.h
        src/Parser/Tokens/Identifier.cpp
        src/Parser/Tokens/Identifier.h
        src/Parser/Tokens/Type/NormalType.cpp
        src/Parser/Tokens/Type/NormalType.h
        src/Parser/Tokens/Type/GenericType.cpp
        src/Parser/Tokens/Type/GenericType.h
        src/Parser/Tokens/Type/Type.h
        src/Parser/TokenForwards.h
        src/Parser/Tokens/Declaration.cpp
        src/Parser/Tokens/Declaration.h
        src/Parser/Tokens/Expression.cpp
        src/Parser/Tokens/Expression.h
        src/Utils/Overload.h src/Parser/Tokens/Literal.cpp src/Parser/Tokens/Literal.h src/Parser/Tokens/Operator.h src/Parser/Tokens/Operator.cpp src/Parser/Tokens/FunctionCall.cpp src/Parser/Tokens/FunctionCall.h src/Parser/Tokens/Block.cpp src/Parser/Tokens/Block.h src/Parser/Tokens/Assignment.cpp src/Parser/Tokens/Assignment.h src/Parser/Tokens/Function.cpp src/Parser/Tokens/Function.h src/Parser/Tokens/Type/DefaultParserTypes.h src/Parser/Tokens/Parameter.cpp src/Parser/Tokens/Parameter.h src/Parser/Tokens/Statement/IfStatement.cpp src/Parser/Tokens/Statement/IfStatement.h src/Parser/Tokens/Statement/ElifStatement.cpp src/Parser/Tokens/Statement/ElifStatement.h src/Parser/Tokens/Statement/ElseStatement.cpp src/Parser/Tokens/Statement/ElseStatement.h src/Utils/Serializer/Serializer.cpp src/Utils/Serializer/Serializer.h src/Utils/Serializer/JsonConverter.cpp src/Utils/Serializer/JsonConverter.h src/Interpreter/Interpreter.cpp src/Interpreter/Interpreter.h src/Interpreter/SymbolTable.cpp src/Interpreter/SymbolTable.h src/Interpreter/SymbolTableTree.cpp src/Interpreter/SymbolTableTree.h src/Interpreter/Language/Variable.cpp src/Interpreter/Language/Variable.h src/Interpreter/Evaluators/ExpressionEvaluator.cpp src/Interpreter/Evaluators/ExpressionEvaluator.h src/Interpreter/Vistors/TokenVisitor.cpp src/Interpreter/Vistors/TokenVisitor.h src/Parser/Tokens/ReturnToken.cpp src/Parser/Tokens/ReturnToken.h src/Interpreter/Evaluators/FunctionEvaluator.cpp src/Interpreter/Evaluators/FunctionEvaluator.h src/TypeChecker/TypeChecker.cpp src/TypeChecker/TypeChecker.h src/Parser/Tokens/Type/TypeComparer.h src/Parser/Tokens/Type/TypeToStringBuilder.h)
target_link_libraries(hasha fmt::fmt nlohmann_json::nlohmann_json magic_enum::magic_enum)

cmake_minimum_required(VERSION 3.12)
project(TKOM)

set(CMAKE_CXX_STANDARD 14)
add_executable(TKOM main.cpp FileReader.cpp FileReader.h main.cpp Token.h TokenType.h Lexer.cpp Lexer.h ErrorHandler.h)
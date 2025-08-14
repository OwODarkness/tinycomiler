cmake_minimum_required(VERSION 3.5.0)
project(TinyCompiler VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(runtime/lexer)
add_subdirectory(runtime/jsonparser)


add_executable(TinyCompiler main.cpp)

target_link_libraries(TinyCompiler PRIVATE LexerLib JsonParserLib)
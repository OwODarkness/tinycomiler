# Lexer/CMakeLists.txt
add_library(LexerLib 
    lexer.cpp lexer.h
    token.cpp token.h
    context.cpp context.h
    symbol.h tag.h
)
target_include_directories(LexerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
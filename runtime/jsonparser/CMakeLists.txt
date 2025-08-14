# jsonparser/CMakeLists.txt
add_library(JsonParserLib 
    jsonparser.h jsonparser.cpp
    json.h    
)
target_include_directories(JsonParserLib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
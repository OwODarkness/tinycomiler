#include <iostream>
#include "runtime/lexer/lexer.h"
#include "runtime/jsonparser/jsonparser.h"
using namespace tinycompiler;
int main(void)
{
    // Lexer L(" hello sd");

    // Token* t = L.scan();

    // std::cout<< *t << std::endl;

    // delete t;

    JsonParser parser;
    try
    {
        Json json = parser.ParseFile("..\\..\\test.json");
        PrintJson(json);
    }
    catch (ParseError err)
    {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
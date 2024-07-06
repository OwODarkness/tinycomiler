#include <iostream>
#include "Lexer/Lexer.h"
int main(void)
{
    Lexer L(" hello sd");
        
    Token* t = L.scan();

    std::cout<< *t << std::endl;
    
    delete t;
}
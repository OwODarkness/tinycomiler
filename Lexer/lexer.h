#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "token.h"
class Lexer{
public:
    Lexer(std::string_view source);
    Token* scan();
protected:
    void next();
    bool next(char target);
    void reserve(const Word& word);
private:
    std::vector<char> txt_buffer;
    std::vector<char>::iterator iter;
    std::map<std::string, Token> words;
    char peek = ' ';
    int line = 1; 
};

#endif// LEXER_H
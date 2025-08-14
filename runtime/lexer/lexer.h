#ifndef TINY_COMPILTER_LEXER_H
#define TINY_COMPILTER_LEXER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "token.h"
namespace tinycompiler
{
    class Lexer
    {
    public:
        Lexer(const std::string& source);
        Token *scan();

    private:
        //fetch next char from buffer
        void next();
        bool next(char target);
        void reserve(const Word &word);
        void ProcessOpetator();
    private:
        std::vector<char> txt_buffer_;
        std::vector<char>::iterator iter_;
        std::unordered_map<std::string, Token> words_;//keep
        char peek_ = ' ';//current char
        int line_ = 1;
    };
}

#endif // LEXER_H
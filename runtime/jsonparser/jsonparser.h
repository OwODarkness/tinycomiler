#ifndef TINYCOMPILER_JSON_PARSER_H
#define TINYCOMPILER_JSON_PARSER_H

#include "json.h"
#include <string>
#include <stdexcept>
#include <stack>

namespace tinycompiler
{
    class JsonParser
    {
    public:
        Json ParseFile(const std::string &file_path);
        void DebugBuffer() const;

    private:
        Json Parse();
        char Next();
        char Peek() const;
        void Expect(char expected);
        void ExpectSequence(const std::string& expected);
        Json ParseValue();
        std::string ParseString();
        char ParseEscape();
        bool ParseBool();
        std::nullptr_t ParseNull();
        float ParseNumber();
        Json ParseArray();
        bool SkipWhitespace();

    private:
        std::string buffer_{};
        size_t index_{};
        std::stack<Json> stack_;
    };

    class ParseError : public std::runtime_error
    {
    public:
        ParseError(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    void PrintJson(const Json &j, int indent = 0);
} // namespace tinycompiler

#endif
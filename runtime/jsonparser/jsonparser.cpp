#include "jsonparser.h"
#include <fstream>
#include <iostream>

namespace tinycompiler
{

    Json JsonParser::ParseFile(const std::string &file_path)
    {
        std::ifstream json_file(file_path, std::ios::binary);
        if (!json_file)
            return nullptr;

        json_file.seekg(0, std::ios::end);
        std::streampos size = json_file.tellg();
        if (size == -1)
            return nullptr;

        json_file.seekg(0, std::ios::beg);

        buffer_.resize(size);
        json_file.read(&buffer_[0], size);

        json_file.close();

        return Parse();
    }

    Json JsonParser::Parse()
    {
        if (!SkipWhitespace())
        {
            return nullptr;
        }
        Expect('{');

        JsonObject object;

        if (SkipWhitespace() && Peek() == '}')
        {
            Next();
            return object;
        }

        while (true)
        {
            if (!SkipWhitespace())
            {
                throw ParseError("Unexpected end while reading object key");
            }

            Expect('"');
            std::string key = ParseString();

            if (!SkipWhitespace())
            {
                throw ParseError("Unexpected end after key");
            }

            Expect(':');
            if (!SkipWhitespace())
            {
                throw ParseError("Unexpected end before value");
            }

            Json value = ParseValue();
            object[key] = std::move(value);

            if (!SkipWhitespace())
            {
                throw ParseError("Unexpected end after value");
            }

            if (Peek() == '}')
            {
                Next();
                break;
            }
            Expect(',');
        }
        return object;
    }

    Json JsonParser::ParseValue()
    {
        char c = Peek();

        if (c == '"')
        {
            Next();
            return ParseString();
        }
        else if (c == '-' || std::isdigit(c))
        {
            return ParseNumber();
        }
        else if (c == 't' || c == 'f')
        {
            return ParseBool();
        }
        else if (c == 'n')
        {
            return ParseNull();
        }
        else if (c == '{')
        {
            return Parse();
        }
        else if (c == '[')
        {
            Next();
            return ParseArray();
        }
        throw ParseError("Unexpected Value whose first char is" + c);
    }

    std::string JsonParser::ParseString()
    {
        std::string res{};
        while (true)
        {
            char c = Next();
            if (c == '"')
            {
                break;
            }
            if (c == '\\')
            {
                res += ParseEscape();
            }
            else if (c == '\n' || c == '\r')
            {
                // raw character
                throw ParseError("Unescaped newline in string");
            }
            else
            {
                res += c;
            }
        }
        return res;
    }

    char JsonParser::ParseEscape()
    {
        char esc = Next();
        char res{};
        switch (esc)
        {
        case '"':
            res = '"';
            break;
        case '\\':
            res = '\\';
            break;
        case '/':
            res = '/';
            break;
        case 'b':
            res = '\b';
            break;
        case 'f':
            res = '\f';
            break;
        case 'n':
            res = '\n';
            break;
        case 'r':
            res = '\r';
            break;
        case 't':
            res = '\t';
            break;
        default:
            throw ParseError("Unexpected charater after \\" + esc);
        }
        return res;
    }
    float JsonParser::ParseNumber()
    {
        float res = 0.0f;
        bool negative = false;

        // handle optional minus sign
        if (Peek() == '-')
        {
            negative = true;
            Next();
        }

        // integer part
        while (index_ < buffer_.size() && std::isdigit(Peek()))
        {
            res = res * 10.0f + (Next() - '0');
        }

        // fractional part
        if (Peek() == '.')
        {
            Next(); // consume '.'
            float frac = 0.0f;
            float factor = 0.1f;
            while (index_ < buffer_.size() && std::isdigit(Peek()))
            {
                frac += factor * (Next() - '0');
                factor *= 0.1f;
            }
            res += frac;
        }

        return negative ? -res : res;
    }

    Json JsonParser::ParseArray()
    {
        JsonArray arr;
        if (SkipWhitespace() && Peek() == ']')
        {
            Next();
            return arr;
        }

        while (true)
        {
            if (!SkipWhitespace())
            {
                throw ParseError("Unexpected end before ]");
            }
            Json value = ParseValue();
            arr.push_back(std::move(value));
            if (!SkipWhitespace())
            {
                throw ParseError("Unexpected end before ]");
            }

            if (Peek() == ']')
            {
                Next();
                break;
            }
            Expect(',');
        }
        return arr;
    }

    char JsonParser::Next()
    {
        if (index_ < buffer_.size())
        {
            return buffer_[index_++];
        }
        return '\0';
    }
    char JsonParser::Peek() const
    {
        if (index_ < buffer_.size())
        {
            return buffer_[index_];
        }
        return '\0';
    }

    bool JsonParser::ParseBool()
    {
        if (Peek() == 't')
        {
            ExpectSequence("true");
            return true;
        }
        else
        {
            ExpectSequence("false");
            return false;
        }
    }
    std::nullptr_t JsonParser::ParseNull()
    {
        ExpectSequence("null");
        return nullptr;
    }

    void JsonParser::Expect(char expected)
    {
        if (index_ > buffer_.size())
        {
            throw ParseError("Unexpected end of input");
        }
        char c = Next();
        if (c != expected)
        {
            std::string msg = "Expected '";
            msg += expected;
            msg += "' but got '";
            msg += c;
            msg += "'";
            throw ParseError(msg);
        }
    }

    void JsonParser::ExpectSequence(const std::string &expected)
    {
        for (char ec : expected)
        {
            if (index_ >= buffer_.size())
            {
                throw ParseError("Unexpected end of input while expecting '" + expected + "'");
            }

            char c = Next(); 
            if (c != ec)
            {
                throw ParseError(std::string("Expected '") + expected + "' but got '" + c + "'");
            }
        }
    }

    bool JsonParser::SkipWhitespace()
    {
        while (index_ < buffer_.size() && std::isspace(buffer_[index_]))
        {
            index_++;
        }
        return index_ < buffer_.size();
    }

    void JsonParser::DebugBuffer() const
    {
        std::cout << buffer_ << "\n";
    }

    void PrintIndent(int indent)
    {
        for (int i = 0; i < indent; ++i)
            std::cout << ' ';
    }

    void PrintJson(const Json &j, int indent)
    {
        std::visit([indent](auto &&arg)
                   {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::nullptr_t>) {
            std::cout << "null";
        } else if constexpr (std::is_same_v<T, bool>) {
            std::cout << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, float>) {
            std::cout << arg;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << '"' << arg << '"';
        } else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
            std::cout << "[ ";
            for (auto& s : arg) std::cout << '"' << s << "\" ";
            std::cout << "]";
        } else if constexpr (std::is_same_v<T, JsonObject>) {
            std::cout << "{\n";
            for (auto& [k,v] : arg) {
                PrintIndent(indent + 2);
                std::cout << '"' << k << "\": ";
                PrintJson(v, indent + 2);
                std::cout << "\n";
            }
            PrintIndent(indent);
            std::cout << "}";
        } else if constexpr (std::is_same_v<T, JsonArray>) {
            std::cout << "[\n";
            for (auto& v : arg) {
                PrintIndent(indent + 2);
                PrintJson(v, indent + 2);
                std::cout << "\n";
            }
            PrintIndent(indent);
            std::cout << "]";
        } }, j);
    }
}
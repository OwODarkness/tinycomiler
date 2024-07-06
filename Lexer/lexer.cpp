#include "lexer.h"
#include <exception>
Lexer::Lexer(std::string_view source)
{
    for (int i = 0; i < source.size(); i++)
    {
        txt_buffer.push_back(source.at(i));
    }
    iter = txt_buffer.begin();
    reserve(Word("if", Tag::IF));
    reserve(Word("else", Tag::ELSE));
    reserve(Word("break", Tag::BREAK));
    reserve(Word("while", Tag::WHILE));
    reserve(Word("do", Tag::DO));
    reserve(Word::_true);
    reserve(Word::_false);
}

void Lexer::reserve(const Word &word)
{
    words.insert({word.value(), word});
}

void Lexer::next()
{
    if (iter == txt_buffer.end())
    {
        peek = ' ';
        //throw std::logic_error("dd");
    }
    peek = *(iter++);
}

bool Lexer::next(char target)
{
    try
    {
        next();
    }
    catch (std::exception &e)
    {
        throw(e);
    }

    if (target == peek)
    {
        return true;
    }
    return false;
}

Token *Lexer::scan()
{
    try
    {
        for (;; next())
        {

            try
            {
                ;
            }
            catch (std::exception &e)
            {
                throw(e);
            }

            if (' ' == peek || '\t' == peek)
            {
                continue;
            }
            else if ('\n' == peek)
            {
                line++;
            }
            else
            {
                break;
            }
        }

        switch (peek)
        {
        case '&':
        {

            if (next('&'))
            {
                return new Word(Word::_and);
            }
            else
            {
                return new Token('&');
            }
            break;
        }

        case '|':
        {
            if (next('|'))
            {
                return new Word(Word::_or);
            }
            else
            {
                return new Token('|');
            }
            break;
        }
        case '=':
        {
            if (next('='))
            {
                return new Word(Word::_eq);
            }
            else
            {
                return new Token('=');
            }
            break;
        }
        case '!':
        {
            if (next('='))
            {
                return new Word(Word::_ne);
            }
            else
            {
                return new Token('!');
            }
            break;
        }
        case '<':
        {
            if (next('='))
            {
                return new Word(Word::_le);
            }
            else
            {
                return new Token('<');
            }
            break;
        }
        case '>':
        {
            if (next('='))
            {
                return new Word(Word::_ge);
            }
            else
            {
                return new Token('>');
            }
            break;
        }
        default:
            break;
        }

        if (std::isdigit(peek))
        {
            int res = 0;
            do
            {
                res = 10 * res + (peek - '0');
                next();
            } while (std::isdigit(peek));
            if ('.' == peek)
            {
                float res2 = res;
                next();
                float ans = 0.1f;
                while (std::isdigit(peek))
                {
                    res2 = res2 + ans * (peek - '0');
                    ans *= 0.1f;
                    next();
                }
                return new Real(res2);
            }
            else
            {
                return new Num(res);
            }
        }

        if (std::isalnum(peek))
        {
            std::string res;
            do
            {
                res.push_back(peek);
                next();
            } while (std::isalnum(peek));

            Word w = Word(res, Tag::ID);

            if (!words.contains(res))
            {
                reserve(w);
            }
            return new Word(w);
        }

        char tmp_c = peek;
        peek = ' ';
        return new Token(tmp_c);
    }
    catch (std::exception &e)
    {
        throw(e);
    }
}
#include "lexer.h"
#include <exception>
#include <iostream>
namespace tinycompiler
{
    Lexer::Lexer(const std::string &source)
    {
        for (int i = 0; i < source.size(); i++)
        {
            txt_buffer_.push_back(source.at(i));
        }
        iter_ = txt_buffer_.begin();
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
        words_.insert({word.value(), word});
    }

    void Lexer::next()
    {
        if (iter_ == txt_buffer_.end())
        {
            peek_ = ' ';
            // throw std::logic_error("dd");
        }
        peek_ = *(iter_++);
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

        if (target == peek_)
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

                // try
                // {
                //     ;
                // }
                // catch (std::exception &e)
                // {
                //     throw(e);
                // }

                //ignore the space
                if (' ' == peek_ || '\t' == peek_)
                {
                    continue;
                }
                else if ('\n' == peek_)
                {
                    line_++;
                }
                else
                {
                    break;
                }
            }

            //check the 
            switch (peek_)
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

            if (std::isdigit(peek_))
            {
                int res = 0;
                do
                {
                    res = 10 * res + (peek_ - '0');
                    next();
                } while (std::isdigit(peek_));
                if ('.' == peek_)
                {
                    float res2 = static_cast<float>(res);
                    next();
                    float ans = 0.1f;
                    while (std::isdigit(peek_))
                    {
                        res2 = res2 + ans * (peek_ - '0');
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

            if (std::isalnum(peek_))
            {
                std::string res;
                do
                {
                    res.push_back(peek_);
                    next();
                } while (std::isalnum(peek_));

                Word w = Word(res, Tag::ID);

                if (!words_.contains(res))
                {
                    reserve(w);
                }
                return new Word(w);
            }

            char tmp_c = peek_;
            peek_ = ' ';
            return new Token(tmp_c);
        }
        catch (std::exception &e)
        {
            throw(e);
        }
    }
}
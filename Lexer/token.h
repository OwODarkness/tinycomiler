#ifndef TOKEN_H
#define TOKEN_H

#include "Tag.h"
#include <string>
#include <iostream>
class Token
{
public:
    Token(int tag) : _tag(tag) {}
    inline int tag() const { return _tag; }
    virtual void toString(std::ostream& out) const;
private:
    const int _tag;
};


class Num : public Token
{
public:
    Num(int value) : Token(Tag::NUM), _value(value) {}
    inline int value() const {return _value;}
    void toString(std::ostream& out)const;
private:
    const int _value;
};


class Real :public Token{
public:
    Real(float value):Token(Tag::REAL), _value(value){}
    inline float value  () const {return _value;}
    void toString(std::ostream& out)const;

private:
    const float _value;
};

class Word: public Token{
public:
    Word(std::string value, int tag):Token(tag), _value(value){}
    inline std::string value() const{return _value;}
    void toString(std::ostream& out)const;

private:
    const std::string _value;
public:
    static const Word _and;
    static const Word _or;
    static const Word _eq;
    static const Word _ne;
    static const Word _le;
    static const Word _ge;
    static const Word _minus;
    static const Word _true;
    static const Word _false;
    static const Word _temp;
};



std::ostream& operator<<(std::ostream& out, const Token& token);

#endif //TOKEN_H
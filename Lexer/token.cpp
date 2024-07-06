#include "token.h"


const Word Word::_and("&&", Tag::AND);
const Word Word::_or("||", Tag::OR);
const Word Word::_eq("==", Tag::EQ);
const Word Word::_ne("!=", Tag::NE);
const Word Word::_le("<=", Tag::LE);
const Word Word::_ge(">=", Tag::GE);
const Word Word::_minus("-", Tag::MINUS);
const Word Word::_true("true", Tag::TRUE);
const Word Word::_false("false", Tag::FALSE);
const Word Word::_temp("t", Tag::TEMP);

void Token::toString(std::ostream& out) const
{
    out << "Token(" << static_cast<char>(tag()) << ")";
}

void Num::toString(std::ostream& out) const
{
    out << "Num(" << value() << ")";
}
void Real::toString(std::ostream& out) const
{
    out << "Real(" << value() << ")";

}
void Word::toString(std::ostream& out) const
{
    out << "word(" << value() << ")";
}


std::ostream& operator<<(std::ostream& out, const Token& token)
{
    token.toString(out);
    return out;
}


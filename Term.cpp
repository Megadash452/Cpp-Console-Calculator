#include "Term.h"

Term::Term(const string& str)
{
	this->termStr = str;
}
Term::Term(const Term& param)
{
	this->termStr = param.termStr;
}


Term Term::add(const string& str)
{

}
Term Term::subtract(const string& str)
{

}
Term Term::multiply(const string& str)
{

}
Term Term::divide(const string& str)
{

}


Term Term::add(const Term& term)
{

}
Term Term::subtract(const Term& term)
{

}
Term Term::multiply(const Term& term)
{

}
Term Term::divide(const Term& term)
{

}


Term Term::operator +(const Term& term) const
{

}
Term Term::operator +(const string& str) const
{

}
Term Term::operator -(const Term& term) const
{

}
Term Term::operator -(const string& str) const
{

}


Term Term::operator*(const Term& term) const
{

}
Term Term::operator*(const string& str) const
{

}
Term Term::operator/(const Term& term) const
{

}
Term Term::operator /(const string& str) const
{

}


void Term::operator +=(const Term& term)
{

}
void Term::operator +=(const string& str)
{

}
void Term::operator -=(const Term& term)
{

}
void Term::operator -=(const string& str)
{

}


void Term::operator *=(const Term& term)
{

}
void Term::operator *=(const string& str)
{

}
void Term::operator /=(const Term& term)
{

}
void Term::operator /=(const string& str)
{

}

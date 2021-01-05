#include "Term.h"

#include "Expression.h"
#include "Lib.h"

Term::Term(const string& str)
{
	this->sign = str[0];

	bool mult = false;
	for (string::const_iterator
		charP = str.begin() + 1;
		charP != str.end();
		charP++)
	{
		this->termStr.push_back(*charP);
		if (*charP == '*' || *charP == '/' || *charP == '^')
			mult = true;
	}

	if (!mult)
		this->value = stod(string(str.begin(), str.end()));
	else
		this->value = 0;
}


Term Term::operator +(const Term& term) const
{
	return std::to_string(this->value + term.value);
}
Term Term::operator +(const string& str) const
{
	Term term(str);
	return std::to_string(this->value + term.value);
}
Term Term::operator -(const Term& term) const
{
	return std::to_string(this->value - term.value);
}
Term Term::operator -(const string& str) const
{
	Term term(str);
	return std::to_string(this->value - term.value);
}


Term Term::operator *(const Term& term) const
{
	return std::to_string(this->value * term.value);
}
Term Term::operator *(const string& str) const
{
	Term term(str);
	return std::to_string(this->value * term.value);
}
Term Term::operator /(const Term& term) const
{
	return std::to_string(this->value / term.value);
}
Term Term::operator /(const string& str) const
{
	Term term(str);
	return std::to_string(this->value / term.value);
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

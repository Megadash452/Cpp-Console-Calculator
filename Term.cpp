#include "Term.h"

#include "Expression.h"
#include "Lib.h"


Term::Term(double num)
{
	this->value = num;
	this->updateStr();
}

Term::Term(const string& str)
{
	int start = 0;
	
	if (str[0] == '-' || str[0] == '+')
	{
		this->sign = str[0];
		start = 1;
	}
	else
		this->sign = '+';

	bool mult = false;
	for (string::const_iterator
		charP = str.begin() + start;
		charP != str.end();
		charP++)
	{
		this->termStr.push_back(*charP);
		if (*charP == '*' || *charP == '/' || *charP == '^')
			mult = true;
	}

	if (!mult)
		try {
			this->value = stod(string(str.begin(), str.end()));
		}
		catch (std::invalid_argument) {
			throw string("Invalid character in Term{" + str + "}");// TODO:bad: use std::exception instead
		}
	else
		this->value = 0;
}

void Term::updateStr()
{
	this->termStr.clear();
	if (this->value < 0) {
		this->sign = '-';
		string tempStr = std::to_string(this->value);
		for (string::const_iterator
			charP = tempStr.begin() + 1;
			charP != tempStr.end();
			charP++)
		{
			this->termStr.push_back(*charP);
		}
	}
	else {
		this->sign = '+';
		this->termStr = std::to_string(this->value);
	}
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

Term Term::operator^(const Term& term) const
{
	return std::to_string(std::pow(this->value, term.value));
}



void Term::operator +=(const Term& term)
{
	this->value += term.value;
	this->updateStr();
}
void Term::operator +=(const string& str)
{
	this->value += Term(str).value;
	this->updateStr();
}
void Term::operator -=(const Term& term)
{
	this->value -= term.value;
	this->updateStr();
}
void Term::operator -=(const string& str)
{
	this->value -= Term(str).value;
	this->updateStr();
}


void Term::operator *=(const Term& term)
{
	this->value *= term.value;
	this->updateStr();
}
void Term::operator *=(const string& str)
{
	this->value *= Term(str).value;
	this->updateStr();
}
void Term::operator /=(const Term& term)
{
	this->value /= term.value;
	this->updateStr();
}
void Term::operator /=(const string& str)
{
	this->value /= Term(str).value;
	this->updateStr();
}

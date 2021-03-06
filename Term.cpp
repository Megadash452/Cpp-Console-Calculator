#include "Term.h"

#include "Expression.h"
#include "Lib.h"


// --- --- Term Parent --- ---
Term::Term()
{
	this->value = 0;
	this->updateStr();
}
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
	int val = this->value + term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}
Term Term::operator +(const string& str) const
{
	Term term(str);
	int val = this->value + term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}
Term Term::operator -(const Term& term) const
{
	int val = this->value - term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}
Term Term::operator -(const string& str) const
{
	Term term(str);
	int val = this->value - term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}


Term Term::operator *(const Term& term) const
{
	int val = this->value * term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}
Term Term::operator *(const string& str) const
{
	Term term(str);
	int val = this->value * term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}
Term Term::operator /(const Term& term) const
{
	int val = this->value / term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
}
Term Term::operator /(const string& str) const
{
	Term term(str);
	int val = this->value / term.value;
	if (val < 0)
		return std::to_string(val);
	else
		return '+' + std::to_string(val);
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

void Term::operator ^=(const Term& term)
{
	this->value = std::pow(this->value, term.value);
}
// --- --- --- ---

// --- --- Arithmetic Term --- ---
ArithmeticTerm::ArithmeticTerm()
{

}
ArithmeticTerm::ArithmeticTerm(double num)
{
	this->value = num;
	this->updateStr();
}
ArithmeticTerm::ArithmeticTerm(const string& str)
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
	this->termStr.clear();
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
// --- --- --- ---


AlgebraicTerm::AlgebraicTerm()
	: coefficient(0), var("0"), exponent(0)
{

}
AlgebraicTerm::AlgebraicTerm(double num)
	: coefficient(num), var("(1)"), exponent(0)
{

}
AlgebraicTerm::AlgebraicTerm(const string& str) /// 2.5(444)^(2) format
{
	string::const_iterator f;
	for (auto charP = str.begin();
		charP != str.end(); charP++)
	{
		if (*charP == '(')
		{
			string str1();
			this->coefficient = stod(string(str.begin(), charP-1));
			f = charP + 1;
			break;
		}
	}

	for (auto charP = f;
		charP == str.end(); charP++)
	{
		if (*charP == ')' && *(charP+1) == '^' && *(charP + 2) == '(')
		{
			this->var = string(f+1, charP-1);
			f = charP + 3;
			break;
		}
	}

	this->exponent = stod(string(f, str.end()-1));
}
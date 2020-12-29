#include "Term.h"
#include "Expression.h"

Term::Term(const string& str)
{
	std::cout << str << ": sign(" << str[0] << "); ";
	this->sign = str[0];

	for (string::const_iterator
		 charP = str.begin() + 1;
		 charP != str.end();
		 charP++)
			this->termStr.push_back(*charP);

	string tempStr(str.begin()+1, str.end());
	std::cout << "Term value string (" << this << "): " << tempStr << std::endl;
	this->value = stoi(tempStr);
	std::cout << this->sign << ' ' << this->termStr << ' ' << this->value << "\n\n";
}
Term::Term(const Term& param)
{
	this->termStr = param.termStr;
}

int Term::integer(char c)
{
	return ((int)c) - 48;
}
int Term::integer(string str, int base)
{
	int num = 0;
	int place = 0;

	for (string::reverse_iterator
		charP = str.rbegin();
		charP != str.rend();
		charP++)
	{
		if (char_in_numbers(*charP) && base == 10)
		{
			num += integer(*charP) * pow(base, place);
			place++;
		}
	}
	return num;
}


Term Term::add(const string& str)
{
	return *this;
}
Term Term::subtract(const string& str)
{
	return *this;
}
Term Term::multiply(const string& str)
{
	return *this;
}
Term Term::divide(const string& str)
{
	return *this;
}


Term Term::add(const Term& term)
{
	return *this;
}
Term Term::subtract(const Term& term)
{
	return *this;
}
Term Term::multiply(const Term& term)
{
	return *this;
}
Term Term::divide(const Term& term)
{
	return *this;
}


Term Term::operator +(const Term& term) const
{
	return *this;
}
Term Term::operator +(const string& str) const
{
	return *this;
}
Term Term::operator -(const Term& term) const
{
	return *this;
}
Term Term::operator -(const string& str) const
{
	return *this;
}


Term Term::operator*(const Term& term) const
{
	return *this;
}
Term Term::operator*(const string& str) const
{
	return *this;
}
Term Term::operator/(const Term& term) const
{
	return *this;
}
Term Term::operator /(const string& str) const
{
	return *this;
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

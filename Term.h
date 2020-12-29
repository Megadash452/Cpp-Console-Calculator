#pragma once
#include <string>
#include <vector>
#include <map>
using string = std::string;
 
// TODO: Goal => 27x^24+25 - (x+2^2)(x-3)
struct Term //Only numbers
{
public:
	string termStr;
	char sign;
	int value;

	Term(const string& str);
	Term(const Term& term);

	int integer(char c);
	int integer(string str, int base = 10);

	
	virtual Term add(const string& str);
	virtual Term subtract(const string& str);
	virtual Term multiply(const string& str);
	virtual Term divide(const string& str);

	virtual Term add(const Term& term);
	virtual Term subtract(const Term& term);
	virtual Term multiply(const Term& term);
	virtual Term divide(const Term& term);

	virtual Term operator +(const Term& term) const;
	virtual Term operator +(const string& str) const;
	virtual Term operator -(const Term& term) const;
	virtual Term operator -(const string& str) const;

	virtual Term operator *(const Term& term) const;
	virtual Term operator *(const string& str) const;
	virtual Term operator /(const Term& term) const;
	virtual Term operator /(const string& str) const;

	virtual void operator +=(const Term& term);
	virtual void operator +=(const string& str);
	virtual void operator -=(const Term& term);
	virtual void operator -=(const string& str);

	virtual void operator *=(const Term& term);
	virtual void operator *=(const string& str);
	virtual void operator /=(const Term& term);
	virtual void operator /=(const string& str);
};

struct AlgebraicTerm : Term // Use this for an Arithmetic Term, but set the exponent (n) = 0;
{
	string termStr;
	char sign;
};

struct ExponentialTerm : Term
{
	string termStr;
	char sign;
};

struct NestedTerm : Term
{
	string termStr;
	char sign;
};
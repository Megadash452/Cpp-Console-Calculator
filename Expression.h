#pragma once
#include "Lib.h"
#include "Term.h"

class Expression
{
public:
	Expression();
	Expression(string str);

	static string parseForRead(string);
	static string parseForPrint(string);

	string expression;
	std::vector<Term> terms;
private:
	string readExp;
};
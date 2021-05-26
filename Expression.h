#pragma once
#include "Lib.h"
//#include "Term.h"

struct Expression_Tree : public lib::Tree
{
	Expression_Tree();
};


class Expression
{
public:
	Expression();
	Expression(string);

	static string parseForRead(string);
	static string parseForPrint(string);

	string expression;
	//Expression_Tree exp_tree;
private:
	string readExp;
};
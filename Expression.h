#pragma once
#include "Utils.h"
#include "Tree.h"


struct ExpTree : public lib::Tree
{
	ExpTree();
	ExpTree(ExpTree&);

};


class Expression
{
public:
	Expression();
	Expression(Expression&);
	Expression(string);

	static string parseForRead(string);
	static string parseForPrint(string);

	string expression;
	ExpTree exp_tree;
private:
	string readExp;
};
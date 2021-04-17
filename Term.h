#pragma once
//#include "Lib.h" fails compiling

struct Term
{
	Term();
};

struct AdditionTerm : public Term
{
	AdditionTerm();
};

struct MultiplicationTerm : public Term
{
	MultiplicationTerm();
};
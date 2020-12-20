#pragma once
#include <string>
#include <vector>
#include <map>
#include <variant>
using string = std::string;
 
// TODO: Goal => 27x^24+25 - (x+2^2)(x-3)
struct Term
{
public:
	string term;
	int a;
	std::map<string, char*> vars;
	int n;

	Term();
};
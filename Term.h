#pragma once
#include <string>
#include <vector>
#include <map>
using string = std::string;
 
// TODO: Goal => 27x^24+25 - (x+2^2)(x-3)
struct Term
{
public:

	Term();
};

struct AlgebraicTerm : Term
{
	// Use this for an Arithmetic Term, but set the ewxponent (n) = 0;

};

struct ExponentialTerm : Term
{

};

struct NestedTerm : Term
{

};
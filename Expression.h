#pragma once
#include <string>
#include <vector>
#include <variant>
using string = std::string;

#include "Lib.h"
#include "Term.h"
#define _allTerms_ ArithmeticTerm, AlgebraicTerm, ExponentialTerm, NestedTerm
#define terms_variant std::variant<ArithmeticTerm, AlgebraicTerm, ExponentialTerm, NestedTerm>

class Expression // Only works for arithmetic Terms, for now.
{
public:
    std::vector<ArithmeticTerm> terms; // st
    string expression;

    static char operators[12];
    static char numbers[10];
    static char constants[5];
    static char alphabet[26];
    static char alphabetUpper[26];
    static char symbols[5];

    enum symbols : unsigned char {
        sigma = 228,
        theta = 233,
        intehralUpper = 244,
        integralLower = 245,
        degree = 248
    };
    
    Expression();
    Expression(string exp);
    Expression(std::vector<string>& vect);

    void print();
    static void print(const Expression& exp);
    void simplify();
    static Expression simplify(Expression exp);

    Expression operator +(const Expression& exp) const;
    Expression operator +(const string& exp) const;
    void operator +=(const Expression& exp);
    void operator +=(const string& exp);

private:
    std::vector<int> mult_div_indexes;
    std::vector<int> exp_indexes;
    std::vector<void (*)(Expression*)> procs;

    void updateTerms(const string& str);
    void updateTerms();
    void updateExpression();
    static string parseString(const string& exp);


    // Expression simplify methods
    static void PEMDAS(Expression* exp);
};


#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <variant>
using string = std::string;

#include "Term.h"
#define _allTerms_ Term, AlgebraicTerm, ExponentialTerm, NestedTerm
// Comparisons
#define char_in_operators(c) (c=='+'||c=='-'||c==(char)241||c=='*'||c=='/'||c=='^'||c=='!'||c=='%'||c=='|'||c=='('||c==')')
#define char_in_numbers(c) (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
#define char_in_constants(c) (c=='e'||c==(char)227||c==(char)237||c==(char)242||c==(char)243)
#define char_in_alphabet(c) (c=='a'||c=='b'||c=='c'||c=='d'||c=='f'||c=='g'||c=='h'||c=='i'||c=='j'||c=='k'||c=='l'||c=='m'||c=='n'||c=='o'||c=='p'||c=='q'||c=='r'||c=='s'||c=='t'||c=='u'||c=='v'||c=='w'||c=='x'||c=='y'||c=='z'||c==(char)159)
#define char_in_alphabetUpper(c) (c=='A'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F'||c=='G'||c=='H'||c=='I'||c=='J'||c=='K'||c=='L'||c=='M'||c=='N'||c=='O'||c=='P'||c=='Q'||c=='R'||c=='S'||c=='T'||c=='U'||c=='V'||c=='W'||c=='X'||c=='Y'||c=='Z')
#define char_in_symbols(c) (c==(char)228||c==(char)233||c==(char)244||c==(char)245||c==(char)248)
#define has_valid_expression_chars(c) (char_in_operators(c)||char_in_numbers(c)||char_in_constants(c)||char_in_alphabet(c)||char_in_alphabetUpper(c)||char_in_symbols(c))

bool char_in_string(char character, string str);

class Expression // ONly works for arithmetic Terms, for now.
{
public:
    std::vector<Term> terms; // st
    string expression;

    static char operators[11];
    static char numbers[10];
    static char constants[5];
    static char alphabet[26];
    static char alphabetUpper[26];
    static char symbols[5];

    static enum symbols : unsigned char {
        sigma = 228,
        theta = 233,
        intehralUpper = 244,
        integralLower = 245,
        degree = 248
    };
    
    Expression(string exp);
    Expression(std::vector<string>& vect);
    void print();
    static void print(const Expression& exp);
    //void simplify();
    static string simplify(const string& exp);

    Expression operator +(const Expression& exp) const;
    Expression operator +(const string& exp) const;
    void operator +=(const Expression& exp);
    void operator +=(const string& exp);

private:
    void updateTerms(const string& str);
    void updateTerms();
    static string parseString(const string& exp);
};


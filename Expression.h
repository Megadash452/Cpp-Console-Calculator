#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <variant>
using string = std::string;

bool char_in_string(char character, string str);

class Expression
{
public:
    std::vector<string> terms; // TODO: Use Term Class instead
    std::string expression;

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
    void simplify();
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


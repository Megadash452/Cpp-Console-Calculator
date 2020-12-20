#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <variant>
#include <map>
using string = std::string;

#include "Expression.h"

//#define print(x) std::cout << x << std::endl

/*#if _DEBUG
#define announce(x) std::cout<<x<<std::endl
#define announce_inExpression(type, exp, x) std::cout<<type<<" ("<<exp[x]<<") in exp["<<x<<']'<<std::endl
#else
#define announce_inExpression(type, exp, x)
#endif*/

bool char_in_string(char character, string str)
{
    for (string::const_iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (character == *charP)
            return true;
    }
    return false;
}

string::const_iterator find_closing(string::const_iterator it, string& str)
{
    if (*it == '(')
    {
        int parenthesisCount = 0;
        for (string::const_iterator i = it; i != str.end(); i++)
        {
            if (*i == '(' && i != it)
                parenthesisCount++;
            if (*i == ')')
            {
                if (parenthesisCount)
                    parenthesisCount--;
                else
                    return i;
            }
        }
    }
}
string::iterator find_closing(string::iterator it, string& str)
{
    if (*it == '(')
    {
        int parenthesisCount = 0;
        for (string::iterator i = it; i != str.end(); i++)
        {
            if (*i == '(' && i != it)
                parenthesisCount++;
            if (*i == ')')
            {
                if (parenthesisCount)
                    parenthesisCount--;
                else
                    return i;
            }
        }
    }
    return it;
}

void vPrint(std::vector<string>& vect)
{
    std::cout << "std::vector: ";
    for (std::vector<string>::const_iterator
        strP = vect.begin();
        strP != vect.end();
        strP++)
    {
        std::cout << *strP << ", ";
    }
    std::cout << std::endl;
}


class Function
{
private:
public:
    static int evaluateExpression(Expression expression)
    {

    }
};

int integer(char c)
{
    return ((int)c) - 48;
}
int integer(string str, int base = 10)
{
    int num = 0;
    int place = 0;

    for (string::reverse_iterator
        charP = str.rbegin();
        charP != str.rend();
        charP++)
    {
        if (char_in_string(*charP, Expression::numbers) && base == 10)
        {
            num += integer(*charP) * pow(base, place);
            place++;
        }
    }
    return num;
}

int main()
{/*
    string x;
    std::cout << std::endl << "enter an expression" << std::endl;
    //getline(std::cin, x);
    x = "2s45";

    Expression e(x);
    //Expression e2("4-5");
    //e += e2;
    //std::cout << e.expression << std::endl;
    //e2.print();

    //Expression::print(e + "4x+7");
    std::cout << Expression::simplify("2+5*2") << std::endl;
    //std::cout << integer(y) << std::endl;

    int end_of_main_function; std::cin >> end_of_main_function;*/

}
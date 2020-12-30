#include "Console calculator.h"
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

string lower_case(string str)
{
    string returnStr;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (*charP >= 65 && *charP <= 90)
            returnStr.push_back(*charP + 32);
        else
            returnStr.push_back(*charP);
    }
    return returnStr;
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


int main()
{
    string action;
    while (true)
    {
        std::cout << "What do you want to do?\nOptions:\n  this\n>";
        getline(std::cin, action);
        action = lower_case(action);

        if (action == "stop" || action == "quit")
        {
            std::cout << "goodbye!";
            exit(0);
        }
        else
        {
            try {
                Expression e(action);
                e.print();
            }
            catch (int e) {
                std::cout << '"' << action << "' cannot be evaluated";
            }
        }
    }
    //Expression e2("4-5");
    //e += e2;
    //std::cout << e.expression << std::endl;
    //e2.print();

    //Expression::print(e + "4x+7");
    //std::cout << Expression::simplify("2+5*2") << std::endl;
    //std::cout << integer(y) << std::endl;*/

    std::cout << "\n-END-";
}
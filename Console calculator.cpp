#include <iostream>
#include <string>
#include <vector>
using string = std::string;

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

string::const_iterator find_closing(string::const_iterator it, string str)
{
    if (*it == '(')
    {
        int parenthesisCount = 0;
        for (string::const_iterator i = it; i != str.end(); i++)
        {
            if (*i == '(' && i != it) // TODO: FIX
                parenthesisCount++;
            if (*i == ')')
            {
                if (parenthesisCount)
                    parenthesisCount--;
                else
                    return i + 1;
            }
        }
    }
}

// -- DO NOT USE! ---
/*string::iterator find_next(string::const_iterator from, string& str)
{
    char target = *from;
    for (string::const_iterator i = from; str.length(); i++)
        if (*i == target)
            return i;
}*/

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

class Term
{
private:
    string term;

public:
};

class Expression
{
private:
    std::vector<string> terms;
    std::string expression;

    void updateTerms(const string& str)
    {
        this->terms.clear();
        string tempTerm;
        for (string::const_iterator
            charP = str.begin();
            charP != str.end();
            charP++)
        {
            if (*charP == '(')
            {
                for (; true; charP++)
                {
                    tempTerm.push_back(*charP);
                    if (*charP == ')')
                        break;
                }
            }
            else if (*charP == '+' || *charP == '-')
            {
                if (charP != str.begin()) this->terms.push_back(tempTerm);
                tempTerm.clear();
                tempTerm.push_back(*charP);
            }
            else
                tempTerm.push_back(*charP);
        }
        this->terms.push_back(tempTerm);
    }

    void updateTerms()
    {
        this->terms.clear();
        string tempTerm;
        for (string::const_iterator
            charP = this->expression.begin();
            charP != this->expression.end();
            charP++)
        {
            if (*charP == '(')
            {
                for (; true; charP++)
                {
                    tempTerm.push_back(*charP);
                    if (*charP == ')')
                        break;
                }
            }
            else if (*charP == '+' || *charP == '-')
            {
                if (charP != this->expression.begin())
                    this->terms.push_back(tempTerm);
                tempTerm.clear();
                tempTerm.push_back(*charP);
            }
            else
                tempTerm.push_back(*charP);
        }
        this->terms.push_back(tempTerm);
    }

    static string parseString(const string& exp)
    {
        string parsed;

        for (string::const_iterator
            charP = exp.begin();
            true;
            charP++)
        {
            if (*charP == '(' ||
                char_in_string(*charP, symbols) ||
                char_in_string(*charP, numbers) ||
                char_in_string(*charP, alphabet) ||
                char_in_string(*charP, constants) ||
                char_in_string(*charP, alphabetUpper))
                parsed.push_back('+');
            break;
        }

        for (string::const_iterator
            charP = exp.begin();
            charP != exp.end();
            charP++)
        {
            if (*charP == '(' &&
                (char_in_string(*(charP - 1), numbers) ||
                    char_in_string(*(charP - 1), constants) ||
                    char_in_string(*(charP - 1), alphabet) ||
                    char_in_string(*(charP - 1), alphabetUpper)))
                parsed.push_back('*');

            if (char_in_string(*charP, operators) ||
                char_in_string(*charP, numbers) ||
                char_in_string(*charP, constants) ||
                char_in_string(*charP, alphabet) ||
                char_in_string(*charP, alphabetUpper))
                parsed.push_back(*charP);
        }
        // TODO: Add more if/else statements to incorporate more characters
        return parsed;
    }

public:
    static char operators[11];
    static char numbers[10];
    static char constants[5];

    static char alphabet[26];
    static char alphabetUpper[26];
    static char symbols[5];


    enum symbols {
        sigma = 228,
        theta = 233,
        integralUpper = 244,
        integralLower = 245,
        degree = 248,
        degrees = 248
    };

    Expression(string exp)
    {
        this->expression = Expression::parseString(exp);
        this->simplify();
        this->updateTerms();
    }

    void print()
    {
        for (std::vector<string>::const_iterator
            strP = this->terms.begin();
            strP != this->terms.end();
            strP++)
                std::cout << *strP << " ";
        std::cout << std::endl;
    }
    static void print(const Expression& exp)
    {
        for (std::vector<string>::const_iterator
            strP = exp.terms.begin();
            strP != exp.terms.end();
            strP++)
                std::cout << *strP << " ";
        std::cout << std::endl;
    }

    void simplify()
    {
        int number = 0;
        for (std::vector<string>::const_iterator
            strP = this->terms.begin();
            strP != this->terms.end();
            strP++)
        {
            string term = *strP;

        }
    }
    static string simplify(const string& exp)
    {
        // Simple arithmetic, for now. 
        // Do not include in this->simplify()
        std::vector<string> tempTerms;
        string tempTerm;
        if (exp[0] != '+' && exp[0] != '-')
            tempTerm.push_back('+');

        // TODO: make anything inside a parenthesis another separate Expression Object
        for (string::const_iterator
            charP = exp.begin();
            charP != exp.end();
            charP++)
        {
            if (*charP == '(')
            {
                for (; true; charP++)
                {
                    tempTerm.push_back(*charP);
                    if (*charP == ')')
                        break;
                }
            }
            else if (*charP == '+' || *charP == '-')
            {
                if (charP != exp.begin())
                    tempTerms.push_back(tempTerm);
                tempTerm.clear();
                tempTerm.push_back(*charP);
            }
            else
                tempTerm.push_back(*charP);
        }
        tempTerms.push_back(tempTerm);

        //vPrint(tempTerms);

        // TODO: identify variable indexes

        int number = 0; // Addition and Subtraction work perfectly with stoi()
        for (std::vector<string>::const_iterator
            strP = tempTerms.begin();
            strP != tempTerms.end();
            strP++)
        {
            int multiply = 1;

            if (char_in_string('(', *strP))
            {
                for (string::const_iterator
                    charP = (*strP).begin();
                    charP != (*strP).end();
                    charP++)
                {
                    if (*charP == '(')
                    {
                        /* try {
                            string str(charP, find_closing(charP, *strP));
                            std::cout << str;
                        }
                        //string nestedTerm(charP + 1, find_closing(charP, *strP);
                        Expression::simplify(nestedTerm); */
                    }
                }   
            }
            else if (char_in_string('*', *strP))
            {
                std::cout << "Multiplication in term: " << *strP << std::endl;

                for (string::const_iterator
                    charP = (*strP).begin();
                    charP != (*strP).end();
                    charP++)
                {
                    char character = *charP;
                    //if (char_in_string(character, Expression::numbers) && char_in_string(*(charP + 1), ))
                }
            }
            else if (char_in_string('/', *strP))
            {
                std::cout << "Division in term: " << *strP << std::endl;
            }
            else
                number += stoi(*strP);
            // TODO: cover multiplication & division
        }
        tempTerms.clear();

        return std::to_string(number);
    }

    // --- Operators --- // NOTE: When an _Expression_ return-type operator is called, the constructor is also called.
    Expression operator +(const Expression& exp) const
    {
        return /*Expression::simplify*/(this->expression + Expression::parseString(exp.expression));
    }
    Expression operator +(const string& exp) const
    {
        return /*Expression::simplify*/(this->expression + Expression::parseString(exp));
    }

    void operator +=(const Expression& exp)
    {
        this->expression += Expression::parseString(exp.expression);
        //this->simplify();
    }
    void operator +=(const string& exp)
    {
        this->expression += Expression::parseString(exp);
        //this->simplify();
    }
};
char Expression::operators[11] = {'+','-',241,'*','/','^','!','%','|','(',')'};
char Expression::numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
char Expression::constants[5] = {'e',227,237,242,243};
char Expression::alphabet[26] = {'a','b','c','d','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 159}; //159 is function f (script-indented) // TODO: Remove i to put in symbols/constants
char Expression::alphabetUpper[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char Expression::symbols[5] = {228,233,244,245,248}; //244 & 245 are integral symbol

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
    int i = 0;

    for (string::reverse_iterator
        charP = str.rbegin();
        charP != str.rend();
        charP++)
    {
        if (char_in_string(*charP, Expression::numbers))
        {
            num += integer(*charP) * pow(10, i);
            i++;
        }
    }
    return num;
}

int main()
{
    /* string x;
    std::cout << std::endl << "enter an expression" << std::endl;
    //getline(std::cin, x);
    x = "2+4+5";

    Expression e(x);
    Expression e2("4-5");
    e += e2;
    e.print();
    e2.print();

    //Expression::print(e + "4x+7");
    std::cout << Expression::simplify("2+3-4+5") << std::endl; */

    string somethingIdk = "el muchacho (de( los ojos (tristes)) vive solo.";
    for (string::const_iterator
        charP = somethingIdk.begin();
        charP != somethingIdk.end();
        charP++)
        if (*charP == '(')
        {
                string str(charP, find_closing(charP, somethingIdk));
                std::cout << str;
        }

    int end_of_main_function; std::cin >> end_of_main_function;
}
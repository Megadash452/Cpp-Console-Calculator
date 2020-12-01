#include <iostream>
#include <string>
#include <vector>
using string = std::string;

//#define print(x) std::cout << x << std::endl

#if _DEBUG
#define announce(x) std::cout<<x<<std::endl
#define announce_inExpression(type, exp, x) std::cout<<type<<" ("<<exp[x]<<") in exp["<<x<<']'<<std::endl
#else
#define announce_inExpression(type, exp, x)
#endif


bool char_in_string(char character, string str)
{
    for (unsigned int i = 0; i < unsigned(str.length()); i++)
    {
        if (character == str[i])
            return true;
    }
    return false;
}

void vPrint(std::vector<string>& vect)
{
    for (std::vector<string>::const_iterator str = vect.begin(); str != vect.end(); str++)
    {
        std::cout << *str << ", ";
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

    Expression(std::string exp)
    {
        this->expression = Expression::parseString(exp);
        //this->simplify();
        this->updateTerms();
    }

    void print()
    {
        std::cout << expression << std::endl;
    }
    static void print(const Expression& exp)
    {
        std::cout << exp.expression << std::endl;
    }

    void updateTerms()
    {
        string tempTerm;
        for (int i = 0; i < this->expression.length(); i++)
        {
            if (expression[i] == '+' || expression[i] == '-')
            {
                if (i != 0) terms.push_back(tempTerm);
                tempTerm.clear();
                tempTerm.push_back(expression[i]);
            }
            else
                tempTerm.push_back(expression[i]);
        }
        terms.push_back(tempTerm);
    }

    void simplify()
    {

    }
    static string simplify(const string& exp)
    {
        // Simple arithmetic, for now.
        std::vector<string> tempTerms;
        string tempTerm;
        if (exp[0] != '+' && exp[0] != '-')
            tempTerm.push_back('+');

        for (int i = 0; i < exp.length(); i++)
        {
            if (exp[i] == '+' || exp[i] == '-')
            {
                if (i != 0)
                    tempTerms.push_back(tempTerm);
                tempTerm.clear();
                tempTerm.push_back(exp[i]);
            }
            else
                tempTerm.push_back(exp[i]);
        }
        tempTerms.push_back(tempTerm);

        vPrint(tempTerms);

        // TODO: identify variable indexes

        int number = 0; // Addition and Subtraction work perfectly with stoi()
        for (std::vector<string>::const_iterator strP = tempTerms.begin(); strP != tempTerms.end(); strP++)
        {
            string term = *strP;
            int multiply = 1;

            if (char_in_string('*', term))
            {
                std::cout << "Multiplication in term: " << term << std::endl;
                for (string::const_iterator charP = term.begin(); charP != term.end(); charP++)
                {
                    char character = *charP;
                    //if (char_in_string(character, Expression::numbers) && char_in_string(*(charP + 1), ))
                }
            }
            else if (char_in_string('/', term))
            {
                std::cout << "Division in term: " << term << std::endl;
            }
            else
                number += stoi(term);
            // TODO: cover multiplication & division
        }
            
            

        tempTerms.clear();

        return std::to_string(number);
    }

    static string parseString(const std::string& exp)
    {
        std::vector<char> charList;

        for (int i = 0; true; i++)
        {
            if (exp[i] == '(' ||
                char_in_string(exp[i], symbols) ||
                char_in_string(exp[i], numbers) ||
                char_in_string(exp[i], alphabet) ||
                char_in_string(exp[i], constants) ||
                char_in_string(exp[i], alphabetUpper))
            {
                charList.push_back('+');
                break;
            }
            else break;
        }

        for (unsigned int i = 0; i < unsigned(exp.length()); i++)
        {
            if (char_in_string(exp[i], operators))
            {
                announce_inExpression("operator", exp, i);
                charList.push_back(exp[i]);
            }
            else if (char_in_string(exp[i], numbers) || char_in_string(exp[i], constants))
            {
                announce_inExpression("nnnumber", exp, i);
                charList.push_back(exp[i]);
            }
            else if (char_in_string(exp[i], alphabet) || char_in_string(exp[i], alphabetUpper))
            {
                announce_inExpression("variable", exp, i);
                charList.push_back(exp[i]);
            }
            // TODO: Add more if/else statements to incorporate more characters
        }
        string returnStr(charList.begin(), charList.end());
        charList.clear();
        std::cout << '\n'; // TODO: Remove
        return returnStr;
    }

    // --- Operators ---
    Expression operator +(const Expression& exp) const
    {
        return /*simplify*/(this->expression + Expression::parseString(exp.expression));
    }
    Expression operator +(const string& exp) const
    {
        return /*simplify*/(this->expression + Expression::parseString(exp));
    }

    void operator +=(const Expression& exp)
    {
        this->expression = this->expression + Expression::parseString(exp.expression);
        //this->simplify();
        this->updateTerms();
    }
    void operator +=(const string& exp)
    {
        this->expression += Expression::parseString(exp);
        //this->simplify();
        this->updateTerms();
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

    for (string::reverse_iterator charP = str.rbegin(); charP != str.rend(); charP++)
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
    string x;
    std::cout << std::endl << "enter an expression" << std::endl;
    getline(std::cin, x);

    Expression e(x);
    //Expression e2("4x-5");
    //e += "4x-5";
    e.print();
    //e2.print();

    Expression::print(e + "4x+7"); // TODO: Fix duplication issue
    std::cout << Expression::simplify("2+3-4+5") << std::endl;

    int end_of_main_function; std::cin >> end_of_main_function;
}
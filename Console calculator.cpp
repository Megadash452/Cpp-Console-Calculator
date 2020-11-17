#include <iostream>
#include <string>
#include <vector>
using namespace std;

#if _DEBUG
#define announce_inExpression(type, exp, x) std::cout << type << " (" << exp[x] << ") in exp[" << x << ']' << std::endl
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

class Term
{
private:
    string term;

public:
};

class Expression
{
private:
    vector<string> terms;
    string expression;

    static char operators[11];
    static char numbers[10];
    static char constants[]; // TODO: Include size of array (incomplete items)

    static char alphabet[26];
    static char alphabetUpper[26];
    static char symbols[]; // TODO: Include size of array (incomplete items)

public:
    Expression(std::string exp)
    {
        this->expression = Expression::parseString(exp);
        this->updateTerms();
    }

    void print()
    {
        cout << expression << endl;
    }

    void updateTerms()
    {
        /*for (int i = 0; i < this->expression.length(); i++)
        {

        }*/
    }

    static string parseString(std::string exp)
    {
        vector<char> charList;

        for (int i = 0; true; i++)
        {
            if (exp[i] != ' ' && (exp[i] != '-' || exp[i] != '+'))
            {
                charList.push_back('+');
                break;
            }
            else if (char_in_string(exp[i], numbers))
            {
                break;
            }
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
                announce_inExpression("number", exp, i);
                charList.push_back(exp[i]);
            }
            else if (char_in_string(exp[i], alphabet))
            {
                announce_inExpression("variable", exp, i);
                charList.push_back(exp[i]);
            }
            // TODO: Add more if/else statements to incorporate more characters
        }
        string returnStr(charList.begin(), charList.end());
        charList.clear();
        return returnStr;
    }

    // --- Operators ---
    Expression operator +(Expression exp)
    {

    }
};
char Expression::operators[11] = {'+','-',241,'*','/','^','!','%','|','(',')'};
char Expression::numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
char Expression::alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; // TODO: Remove e and i to put on symbols/constants
char Expression::constants[] = {227,237,242,243};
char Expression::alphabetUpper[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char Expression::symbols[] = {228,233,244,245,248}; //244 & 245 are integral symbol

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
    string x;
    cout << endl << "enter an expression" << endl;
    getline(cin, x);

    Expression e(x);
    e.print();

    int end_of_main_function; cin >> end_of_main_function;
}
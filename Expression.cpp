#include "Expression.h"

char Expression::operators[11] = { '+','-',241,'*','/','^','!','%','|','(',')' };
char Expression::numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
char Expression::constants[5] = { 'e',227,237,242,243 };
char Expression::alphabet[26] = { 'a','b','c','d','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 159 }; //159 is function f (script-indented) // TODO: Remove i to put in symbols/constants
char Expression::alphabetUpper[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char Expression::symbols[5] = { 228,233,244,245,248 }; //244 & 245 are integral symbol 

Expression::Expression(string exp)
{
    this->expression = Expression::parseString(exp);
    this->simplify();
    this->updateTerms();
}
Expression::Expression(std::vector<string>& vect)
{
    for (std::vector<string>::const_iterator
        strP = vect.begin();
        strP != vect.end();
        strP++)
        this->expression += Expression::parseString(*strP);
    this->simplify();
    this->updateTerms();
}

void Expression::print()
{
    for (std::vector<string>::const_iterator
        strP = this->terms.begin();
        strP != this->terms.end();
        strP++)
        std::cout << *strP << " ";
    std::cout << std::endl;
}
void Expression::print(const Expression& exp)
{
    for (std::vector<string>::const_iterator
        strP = exp.terms.begin();
        strP != exp.terms.end();
        strP++)
        std::cout << *strP << " ";
    std::cout << std::endl;
}

void Expression::simplify()
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
string Expression::simplify(const string& exp) // TODO: 
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


    int number = 0;
    for (std::vector<string>::iterator
        strP = tempTerms.begin();
        strP != tempTerms.end();
        strP++)
    {
        int multiply = 1;

        /*if (char_in_string('(', *strP))
        {
            for (string::iterator
                charP = (*strP).begin();
                charP != (*strP).end();
                charP++)
            {
                if (*charP == '(')
                {
                    string nestedTerm(charP + 1, find_closing(charP, *strP));
                    std::cout << Expression::simplify(nestedTerm) << std::endl;
                    number += stoi(Expression::simplify(nestedTerm));
                }
            }
        }
        else*/ if (char_in_string('*', *strP))
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
    number += stoi(*strP); // Addition and Subtraction work perfectly with stoi()
// TODO: cover multiplication & division
    }
    tempTerms.clear();

    return std::to_string(number);
}


// --- Operators --- // NOTE: When an _Expression_ return-type operator is called, the constructor is also called.
Expression Expression::operator +(const Expression& exp) const
{
    return /*Expression::simplify*/(this->expression + Expression::parseString(exp.expression));
}
Expression Expression::operator +(const string& exp) const
{
    return /*Expression::simplify*/(this->expression + Expression::parseString(exp));
}
void Expression::operator +=(const Expression& exp)
{
    this->expression += Expression::parseString(exp.expression);
    //this->simplify();
}
void Expression::operator +=(const string& exp)
{
    this->expression += Expression::parseString(exp);
    //this->simplify();
}

void Expression::updateTerms(const string& str)
{ // update to suit Terms object
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
void Expression::updateTerms() // update to suit the Terms object
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

string Expression::parseString(const string& exp)
{
    string parsed;

    for (string::const_iterator
        charP = exp.begin();
        charP != exp.end();
        charP++)
    {
        if (char_in_string(*charP, Expression::symbols) ||
            char_in_string(*charP, Expression::numbers) ||
            char_in_string(*charP, Expression::alphabet) ||
            char_in_string(*charP, Expression::constants) ||
            char_in_string(*charP, Expression::operators) ||
            char_in_string(*charP, Expression::alphabetUpper))
                parsed.push_back(*charP);
    }

    if (parsed[0] == '|' ||
        parsed[0] == '(' ||
        char_in_string(parsed[0], Expression::symbols) ||
        char_in_string(parsed[0], Expression::numbers) ||
        char_in_string(parsed[0], Expression::alphabet) ||
        char_in_string(parsed[0], Expression::constants) ||
        char_in_string(parsed[0], Expression::alphabetUpper))
            parsed = '+' + parsed;
}
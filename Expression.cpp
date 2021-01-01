#include "Expression.h"

char Expression::operators[11] = { '+','-',(char)241,'*','/','^','!','%','|','(',')' };
char Expression::numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
char Expression::constants[5] = { 'e',(char)227,(char)237,(char)242,(char)243 };
char Expression::alphabet[26] = { 'a','b','c','d','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',(char)159 }; //159 is function f (script-indented) // TODO: Remove i to put in symbols/constants
char Expression::alphabetUpper[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char Expression::symbols[5] = { (char)228,(char)233,(char)244,(char)245,(char)248 }; //244 & 245 are integral symbol 

Expression::Expression(string exp)
{
    this->expression = Expression::parseString(exp);
    this->updateTerms();
    this->simplify();
}
Expression::Expression(std::vector<string>& vect)
{
    for (std::vector<string>::const_iterator
        strP = vect.begin();
        strP != vect.end();
        strP++)
        this->expression += Expression::parseString(*strP);
    this->updateTerms();
    this->simplify();
}

void Expression::print()
{
    for (std::vector<Term>::const_iterator
        termP = this->terms.begin();
        termP != this->terms.end();
        termP++)
        std::cout << termP->sign << termP->termStr << " ";
    std::cout << std::endl;
}
void Expression::print(const Expression& exp)
{
    for (std::vector<Term>::const_iterator
        termP = exp.terms.begin();
        termP != exp.terms.end();
        termP++)
        std::cout << termP->sign << termP->termStr << " int(" << termP->value << ") ";
    std::cout << std::endl;
}

void Expression::simplify()
{
    // --Multiplying/Dividing
    for (std::vector<int>::iterator
        indP = this->mult_div_indexes.begin();
        indP != this->mult_div_indexes.end();
        indP++)
    {
        double multiplication = 1;
        std::vector<string> tempVect;
        lib::split(this->terms[*indP].termStr, "*/", tempVect, true);
        tempVect[0] = this->terms[*indP].sign + tempVect[0];

        for (std::vector<string>::iterator
            sign = tempVect.begin() + 1;
            sign != tempVect.end();
            sign += 2)
        {
            if (*sign == "*" && sign == tempVect.begin() + 1)
                multiplication = stod(*(sign - 1)) * stod(*(sign + 1));
            else if (* sign == "*")
                multiplication *= stod(*(sign + 1));

            else if (*sign == "/" && sign == tempVect.begin() + 1)
                multiplication = stod(*(sign - 1)) / stod(*(sign + 1));
            else if (*sign == "/")
                multiplication / stod(*(sign + 1));
        }

        if (multiplication >= 0) {
            Term tempTerm('+' + std::to_string(multiplication));
            this->terms[*indP] = tempTerm;
        }
        else {
            Term tempTerm(std::to_string(multiplication));
            this->terms[*indP] = tempTerm;
        }
    }
    this->mult_div_indexes.clear();

    // --Adding/Subtracting
    int addition = 0;
    std::vector<Term> arithmeticTerms;
    for (std::vector<Term>::iterator
        termP = this->terms.begin();
        termP != this->terms.end();
        termP++)
    {
        addition += termP->value;
    }
    if (addition >= 0)
        this->expression = /*'+' + */std::to_string(addition);
    else
        this->expression = std::to_string(addition);
    this->updateTerms();
}
string Expression::simplify(string exp) // TODO: 
{
    Expression tempEx(exp);

    return tempEx.expression;
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
{
    this->expression = Expression::parseString(str);
    this->updateTerms();
}
void Expression::updateTerms()
{
    this->terms.clear();
    string tempStr;
    int index = 0;
    bool mult_on_this_term = false;
    for (string::iterator
         charP = this->expression.begin();
         charP != this->expression.end();
         charP++)
    {
        if (charP != this->expression.begin() && (*charP == '+' || *charP == '-') && !(*(charP - 1) == '*' || *(charP - 1) == '/'))
        {
            Term tempTerm(tempStr);
            this->terms.push_back(tempTerm);
            tempStr.clear();
            tempStr.push_back(*charP);
            index++;
            mult_on_this_term = false;
        }
        else if ((*charP == '*' || *charP == '/') && !(mult_on_this_term))
        {
            this->mult_div_indexes.push_back(index);
            mult_on_this_term = true;
            tempStr += *charP;
        }
        else
            tempStr += *charP;
    }
    Term tempTerm(tempStr);
    this->terms.push_back(tempTerm);
    tempStr.clear();
}

string Expression::parseString(const string& exp)
{
    string parsed;
    for (string::const_iterator
        charP = exp.begin();
        charP != exp.end();
        charP++)
    {
        if (has_valid_expression_chars(*charP))
            parsed.push_back(*charP);
    }

    if (parsed[0] == '|' ||
        parsed[0] == '(' ||
        char_in_symbols(parsed[0]) ||
        char_in_numbers(parsed[0]) ||
        char_in_alphabet(parsed[0]) ||
        char_in_constants(parsed[0]) ||
        char_in_alphabetUpper(parsed[0]))
            parsed = '+' + parsed;

    return parsed;
}
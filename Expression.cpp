#include "Expression.h"

char Expression::operators[12] = { '+','-',(char)241,'*','/','^','!','%','|','(',')','.' };
char Expression::numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
char Expression::constants[5] = { 'e',(char)227,(char)237,(char)242,(char)243 };
char Expression::alphabet[26] = { 'a','b','c','d','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',(char)159 }; //159 is function f (script-indented) // TODO: Remove i to put in symbols/constants
char Expression::alphabetUpper[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char Expression::symbols[5] = { (char)228,(char)233,(char)244,(char)245,(char)248 }; //244 & 245 are integral symbol 

Expression::Expression()
{

}
Expression::Expression(string exp)
{
    this->expression = Expression::parseString(exp);
    this->updateTerms();
}
Expression::Expression(std::vector<string>& vect)
{
    for (std::vector<string>::const_iterator
        strP = vect.begin();
        strP != vect.end();
        strP++)
        this->expression += Expression::parseString(*strP);
    this->updateTerms();
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
    this->PEMDAS();
}
Expression Expression::simplify(Expression exp)
{
    exp.simplify();
    return exp;
}


// --- Expression Simplification Methods ---
void Expression::PEMDAS()
{
    // --Exponent
    for (std::vector<int>::iterator
        indP = this->exp_indexes.begin();
        indP != this->exp_indexes.end();
        indP++)
    {
        //TODO: finish exponent calculation in Expression
        double result;
        std::vector<string> tempVect;
    }

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
            else if (*sign == "*")
                multiplication *= stod(*(sign + 1));

            else if (*sign == "/" && sign == tempVect.begin() + 1)
                multiplication = stod(*(sign - 1)) / stod(*(sign + 1));
            else if (*sign == "/")
                multiplication /= stod(*(sign + 1));
        }

        if (multiplication >= 0)
            this->terms[*indP] = Term('+' + std::to_string(multiplication));
        else
            this->terms[*indP] = Term(std::to_string(multiplication));
    }
    this->mult_div_indexes.clear();

    // --Adding/Subtracting
    for (std::vector<Term>::reverse_iterator
        termP = this->terms.rbegin() + 1;
        termP != this->terms.rend();)
    {
        *termP += *(termP - 1);
        termP++;
        this->terms.erase(this->terms.end() - 1);
    }
    this->updateExpression();
}
// --- ---


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
    bool exp_on_this_term = false;

    for (string::iterator
         charP = this->expression.begin();
         charP != this->expression.end();
         charP++)
    {
        if (charP != this->expression.begin() && (*charP == '+' || *charP == '-')) // might remove last && for optimization
        {
            this->terms.push_back(Term(tempStr));
            index++;
            mult_on_this_term = false;
            exp_on_this_term = false;
            tempStr.clear();
            if (*charP == '-' && *(charP + 1) == '+')
            {
                tempStr.push_back('-');
                charP++;
                continue;
            }
            else if ((*charP == '-' || *charP == '+') && *(charP + 1) == *charP)
            {
                tempStr.push_back('-');
                charP++;
                continue;
            }
        }
        else if ((*charP == '*' || *charP == '/') && !mult_on_this_term)
        {
            this->mult_div_indexes.push_back(index);
            mult_on_this_term = true;
            tempStr += *charP;
        }
        else if (*charP == '^' && !exp_on_this_term)
        {
            this->exp_indexes.push_back(index);
            exp_on_this_term = true;
            tempStr += *charP;
        }
        else
            tempStr += *charP;
    }
    this->terms.push_back(Term(tempStr));
    tempStr.clear();
}
void Expression::updateExpression()
{
    this->expression.clear();
    for (std::vector<Term>::iterator
        termP = this->terms.begin();
        termP != this->terms.end();
        termP++)
    {
        this->expression.push_back(termP->sign);
        this->expression += termP->termStr;
    }
}

string Expression::parseString(const string& exp)
{
    string parsed;
    for (string::const_iterator
        charP = exp.begin();
        charP != exp.end();
        charP++)
    {
        if (char_in_operators(*charP) &&
            char_in_operators(*(charP+1)) &&
            char_in_operators(*(charP+2)))
                throw string("Invalid Expression Syntax");
        else if (has_valid_expression_chars(*charP))
            parsed.push_back(*charP);
    }

    if (parsed[0] != '+' || parsed[0] != '-' ||
        parsed[0] != (char)241 ||
        parsed[0] != '*' || parsed[0] != '/' ||
        parsed[0] != '^')
            parsed = '+' + parsed;

    return parsed;
}
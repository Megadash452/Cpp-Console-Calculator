#include "Expression.h"


Expression::Expression()
{

}
Expression::Expression(string str)
{
	this->readExp = Expression::parseForRead(str);
	this->expression = Expression::parseForPrint(this->readExp);
}

string Expression::parseForRead(string str)
{
    string parsed;
    for (string::iterator
        charP = str.begin();
        charP < str.end();
        charP++)
    {
        try {
            if (*charP == '*' && *(charP + 1) == '*')
            {
                str.replace(charP, charP + 2, "^");
            }
            if ((*charP == '^' || *charP == '/') && *(charP + 1) != '(')
            {
                // insert opening parenthesis
                auto charT = charP;
                str.insert(charP + 1, '(');
                charP = charT;
                // insert closing parenthesis
                for (string::iterator i = charP+2;
                    i != str.end(); i++)
                    if (char_in_operators(*i) && i != str.end() - 1)
                    {
                        str.insert(i, ')');
                        break;
                    }
                    else if (i == str.end() - 1 && *i != ')')
                    {
                        str.push_back(')');
                        break;
                    }
            }

            if (*charP == '/' && *(charP - 1) != ')')
            {
                str.insert(charP, ')');
                for (string::reverse_iterator
                    i = static_cast<string::reverse_iterator>(charP) - 1;
                    i != str.rend()-1; i++)
                {
                    if (i == str.rend() - 1 && *i != '(')
                        str = "(" + str;
                }
            }

            if ((charP != str.end()-1 && charP != str.begin()) &&
                *(charP) == '(' &&
                (!char_in_operators(*(charP-1)) || *(charP-1) == ')'))
            {
                str.insert(charP, '*');
            }


            // put last
           /* if ((charP < str.end()-3) &&
                char_in_operators(*charP) &&
                char_in_operators(*(charP + 1)) &&
                char_in_operators(*(charP + 2)))
                throw string("Invalid Expression Syntax");
            else if (has_valid_expression_chars(*charP))
                parsed.push_back(*charP);*/
        }
        catch (std::out_of_range e) {
            break;
        }
    }

    /*if (parsed[0] != '+' || parsed[0] != '-' ||
        parsed[0] != (char)241 ||
        parsed[0] != '*' || parsed[0] != '/' ||
        parsed[0] != '^')
        parsed = '+' + parsed;*/
    
    //return parsed;
    return str;
}

string Expression::parseForPrint(string str)
{
	return str;
}
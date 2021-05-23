#include "Expression.h"

/// --- Expression Tree ---

//Expression_Tree::Expression_Tree()
//	: lib::Tree{"Expression"}
//{
//
//}



/// --- Expression ---

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
	/*format:
		from "2/3-4**5+3*8"
		to   "(2)/(3)-4^(5)+3*8"
	*/

	for (auto charP = str.begin();
		charP < str.end(); charP++)
	{
		try {
			// remove redundant ARITHMETIC
			if ((*charP == '+' && *(charP + 1) == '+') ||
				(*charP == '+' && *(charP + 1) == '-'))
				str.erase(charP);
			else if (*charP == '-' && *(charP + 1) == '+')
				str.erase(charP + 1);
			else if (*charP == '-' && *(charP + 1) == '-')
				str.replace(charP + 1, charP + 2, "(-1)");

			// EXPONENT "**": change to symbol "^"
			if (*charP == '*' && *(charP + 1) == '*')
				str.replace(charP, charP + 2, "^");

			/* insert MULTIPLICATION "*" when symbol not present
			   AND when MULTIPLICATION applicable
			*/
			if (charP < str.end() - 1 && (*(charP + 1) == '(' || char_in_alphabet(*(charP + 1)) || char_in_alphabetUpper(*(charP + 1)) ||
				char_in_numbers(*(charP + 1)) || char_in_constants(*(charP + 1)) || char_in_symbols(*(charP + 1))))
				if (*charP != '*' && *charP == ')')
					str.insert(charP + 1, '*');

			if (charP > str.begin() && (*(charP - 1) == ')' || char_in_alphabet(*(charP - 1)) || char_in_alphabetUpper(*(charP - 1)) ||
				char_in_numbers(*(charP - 1)) || char_in_constants(*(charP - 1)) || char_in_symbols(*(charP - 1))))
				if (*charP != '*' && *charP == '(')
					str.insert(charP, '*');

			/* EXPONENT symbol "^" and DIVISION symbol "/"
			   append PARENTHESIS after symbol
			*/
			if ((*charP == '^' || *charP == '/' /*||
				(*charP == '*' && (*charP == '+' || *charP == '-'))*/)
				&& *(charP + 1) != '(')
			{
				// append OPENING PARENTHESIS
				str.insert(charP+1, '(');

				// append CLOSING PARENTHESIS
				for (auto it = charP + 1; it < str.end(); it++)
					if (char_in_operators(*it) &&  *it != '(')
					{
						str.insert(it, ')');
						break;
					}
					else if (it == str.end() - 1)
					{
						str.push_back(')');
						break;
					}

				// append PARENTHESIS before symbol
				if (/**charP == '/' && */*(charP - 1) != ')')
				{
					// append CLOSING PARENTHESIS
					str.insert(charP, ')');

					// append OPENING PARENTHESIS
					for (auto it = static_cast<string::reverse_iterator>(charP);
						it < str.rend(); it++)
						if (char_in_operators(*it) && *it != ')')
						{
							//println(*it.base());
							str.insert(it.base(), '(');
							break;
						}
						else if (it == str.rend() - 1)
						{
							str.insert(str.begin(), '(');
							break;
						}
				}
			}
		}
		catch (lib::syntax_error e) {
			throw(e);
			break;
		}
		catch (std::exception) {
			throw(lib::syntax_error{ "Bad syntax around \"" + string(charP - 1, charP + 2) + "\"" });
			break;
		}
	}

	if (str[0] != '+' && str[0] != '-')
			str = '+' + str;

    return str;
}

string Expression::parseForPrint(string str)
{
	return str;
}
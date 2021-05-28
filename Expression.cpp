#include "Expression.h"

/// --- Expression Tree ---

Exp_Tree::Exp_Tree()
	: lib::Tree{ "Expression<>" },
	first_node(new Exp_Tree::Exp_Node),
	entry_node(first_node)
{

}

Exp_Tree::Exp_Tree(string exp)
	: lib::Tree{ "Expression<" + exp + ">"},
	first_node(new Exp_Tree::Exp_Node),
	entry_node(first_node)
{
	this->create_nodes_from_exp(exp);
}

Exp_Tree::Exp_Tree(Exp_Tree& t)
	: lib::Tree{ t },
	first_node(new Exp_Tree::Exp_Node),
	entry_node(first_node)
{

}

void Exp_Tree::create_nodes_from_exp(string exp)
{
	this->first_node->create_nodes_from_exp(exp);
}

void Exp_Tree::reset_nodes(string exp)
{
	for (Exp_Node* child : this->first_node->children)
		delete child;

	this->create_nodes_from_exp(exp);
}

//void Exp_Tree::operator=(Exp_Tree& t)
//{
//	this->first_node = t.first_node;
//	this->entry_node = t.first_node;
//	this->name = t.name;
//	this->used_node_ids = t.used_node_ids;
//}

/// --- --- --- ---



/// --- Expression Tree Node ---

void Exp_Tree::Exp_Node::create_nodes_from_exp(string exp)
{
	// TODO: COMPLETE THIS

	for (auto charP = exp.begin();
		charP != exp.end(); charP++)
	{
		try {
			
		}
		catch (lib::calc_exception e) {

		}
	}
}

/// --- --- --- ---



/// --- Expression ---

Expression::Expression()
	: readExp(""), exp_tree(""), expression("")
{

}
Expression::Expression(Expression& e)
	: readExp(e.readExp), exp_tree(e.exp_tree), expression(e.expression)
{

}

Expression::Expression(string str)
	: readExp(Expression::parseForRead(str)), exp_tree(readExp)
{
	this->expression = Expression::parseForPrint(this->readExp);
}

string Expression::parseForRead(string str)
{
	/*format:
		from "2/3-4**5+3*8"
		to   "(2)/(3)-4^(5)+3*8"
	*/

	// remove spaces
	for (auto charP = str.begin();
		charP < str.end(); charP++)
		if (*charP == ' ')
			str.erase(charP);

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
			else if (*charP == '-' && *(charP + 1) == '-') {
				str.replace(charP, charP + 2, "+(-1)"); // TODO: Make parenthesis better
			}
				

			// EXPONENT "**": change to symbol "^"
			if (*charP == '*' && *(charP + 1) == '*')
				str.replace(charP, charP + 2, "^");

			/* insert MULTIPLICATION "*" when symbol not present
			   AND when MULTIPLICATION applicable
			*/
			if (charP < str.end() - 1 && (*(charP + 1) == '(' ||
				char_in_alphabet(*(charP + 1))      ||
				char_in_alphabetUpper(*(charP + 1)) ||
				char_in_numbers(*(charP + 1))       ||
				char_in_constants(*(charP + 1))     ||
				char_in_symbols(*(charP + 1))))
					if (*charP != '*' && *charP == ')')
						str.insert(charP + 1, '*');

			if (charP > str.begin() && (*(charP - 1) == ')' ||
				char_in_alphabet(*(charP - 1))      ||
				char_in_alphabetUpper(*(charP - 1)) ||
				char_in_numbers(*(charP - 1))       ||
				char_in_constants(*(charP - 1))     ||
				char_in_symbols(*(charP - 1))))
					if (*charP != '*' && *charP == '(')
						str.insert(charP, '*');

			/* EXPONENT symbol "^" and DIVISION symbol "/"
			   append PARENTHESIS after symbol
			*/
			if ((*charP == '^' || *charP == '/' || *charP == '*' /*||
				(*charP == '*' && (*charP == '+' || *charP == '-'))*/)
				&& *(charP + 1) != '(')
			{
				// append OPENING PARENTHESIS
				str.insert(charP+1, '(');

				// catch charP
				auto temp = (int)(charP - str.begin());

				// append CLOSING PARENTHESIS
				for (int it = 1; charP + it < str.end(); it++)
					if (char_in_operators(*(charP + it)) &&  *(charP + it) != '(')
					{
						str.insert((charP + it), ')');
						break;
					}
					else if ((charP + it) == str.end() - 1)
					{
						str.push_back(')');
						break;
					}
				// restate charP
				charP = str.begin() + temp;

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

Expression& Expression::simplify()
{
	// TODO: insert return statement here
	return *this;
}

/// --- --- --- ---
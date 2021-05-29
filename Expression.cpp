#include "Expression.h"
//#include "Console.h"

/// --- Expression Tree ---

Exp_Tree::Exp_Tree()
	: lib::Tree{ "Expression<>" },
	first_node(new Exp_Tree::Exp_Node),
	entry_node(first_node)
{

}

Exp_Tree::Exp_Tree(string exp)
	: lib::Tree{ "Expression<" + exp + ">"},
	first_node(new Exp_Tree::Exp_Node{ exp }),
	entry_node(first_node)
{
	//this->create_nodes_from_exp(exp);
}

Exp_Tree::Exp_Tree(Exp_Tree& t)
	: lib::Tree{ t },
	first_node(t.first_node),
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

//Exp_Tree::Exp_Node* Exp_Tree::Exp_Node::append_child(Exp_Node* _child)
//{
//	_child->set_parent(this);
//	_child->set_used_ids(this, this->used_ids);
//	if (!_child->id)
//	{
//		for (unsigned int id : *(this->used_ids))
//			_child->id++;
//		_child->id++;
//		this->used_ids->push_back(_child->id);
//	}
//	this->children.push_back(_child);
//	return _child;
//}

void Exp_Tree::Exp_Node::create_nodes_from_exp(string exp)
{
	// TODO: COMPLETE THIS

	console << "building Node...";
	for (auto charP = exp.begin();
		charP != exp.end(); charP++)
	{
		Add_Node* current_add = nullptr;
		try {
			if (*charP == '(' ||
				*charP == '[' ||
				*charP == '{' ||
				*charP == '|')
				charP = lib::find_closing(charP);

			if (*charP == '+' && charP != exp.begin())
			{
				if (current_add != nullptr)
					;
				else
					;// current_add = this->append_child(new Add_Node{});

				// TODO: Handle a little differently
			}

			if (*charP == '/')
			{
				string dividend{ lib::find_opening(charP - 1) + 1, charP - 1 };
				string divisor{ charP + 2, lib::find_closing(charP + 1) };
				
				this->append_child(new Div_Node{ dividend, divisor });
			}
		}
		catch (std::out_of_range e) {

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


string::iterator Expression::wrap_in_nester_forward(string& str, string::iterator begin, char nester)
{
	// nester must be beignner nest (e.g. '(', '[', '{', '<', etc.)
	char closer = lib::closeDelims[nester];

	// append OPENING NESTER
	begin = str.insert(begin, nester);

	// append CLOSING NESTER
	// append before the next operrator
	// if no operator found, place nester at the end of str
	for (int it = 1; begin + it < str.end(); it++)
		if (char_in_operators(*(begin + it)) &&
			*(begin + it) != nester &&
			it != 1)
		{
			begin = str.insert(begin + it, closer) - it;
			break;
		}
		else if ((begin + it) == str.end() - 1)
		{
			str.push_back(closer);
			break;
		}
	return begin;
}
string::iterator Expression::wrap_in_nester_back(string& str, string::iterator begin, char nester)
{
	// nester must be ender nest (e.g. ')', '}', '}', '>', etc.)
	char closer = lib::openDelims[nester];

	// append CLOSING NESTER
	begin = str.insert(begin, nester);

	// append OPENING NESTER
	// append before the next operrator
	// if no operator found, place nester at the beginning of str
	for (int it = 0; begin - it > str.begin(); it--)
		if (char_in_operators(*(begin - it)) && 
			*(begin + it) != nester &&
			it != 0)
		{
			begin = str.insert(begin + it, closer) - it;
			break;
		}
		else if ((begin + it) == str.begin())
		{
			str.push_back(closer);
			break;
		}

	return begin;
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
			if (*charP == '+' && *(charP + 1) == '+')
				charP = str.erase(charP);
			else if (*charP == '+' && *(charP + 1) == '-')
				charP = Expression::wrap_in_nester_forward(str, charP + 1) - 1;
			else if (*charP == '-' && *(charP + 1) == '+') {
				charP = str.erase(charP + 1) - 1;
				charP = str.insert(charP, '+');
				charP = Expression::wrap_in_nester_forward(str, charP + 1) - 1;
			}
			else if (*charP == '-' && *(charP + 1) == '-') {
				charP = str.erase(charP, charP + 2);
				charP = str.insert(charP, '+');
			}

			// TODO: convert subtraction to negative addition in Node assignment
			//       perhaps even do the entire code above in node assignment?*/
				

			// EXPONENT "**": change to symbol "^"
			if (*charP == '*' && *(charP + 1) == '*')
				str.replace(charP, charP + 2, "^");

			/* insert MULTIPLICATION "*" when symbol not present
			   AND when MULTIPLICATION applicable
			*/
			if (charP > str.begin() && charP < str.end()-1)
			{
				if (*(charP + 1) == '('                 ||
					char_in_alphabet(*(charP + 1))      ||
					char_in_alphabetUpper(*(charP + 1)) ||
					char_in_numbers(*(charP + 1))       ||
					char_in_constants(*(charP + 1))     ||
					char_in_symbols(*(charP + 1)))
						if (*charP != '*' && *charP == ')')
							charP = str.insert(charP + 1, '*') - 1;

				if (*(charP - 1) == ')'                 ||
					char_in_alphabet(*(charP - 1))      ||
					char_in_alphabetUpper(*(charP - 1)) ||
					char_in_numbers(*(charP - 1))       ||
					char_in_constants(*(charP - 1))     ||
					char_in_symbols(*(charP - 1)))
						if (*charP != '*' && *charP == '(')
							charP = str.insert(charP, '*');
			}

			/* EXPONENT symbol "^" and DIVISION symbol "/"
			   append PARENTHESIS after symbol
			*/
			if (*charP == '^' || *charP == '/' || *charP == '*' /*||
				(*charP == '*' && (*charP == '+' || *charP == '-'))*/)
			{
				// append PARENTHESIS after symbol
				if (*(charP + 1) != '(')
					charP = Expression::wrap_in_nester_forward(str, charP + 1) - 1;

				// append PARENTHESIS before symbol
				if (*(charP - 1) != ')')
					charP = Expression::wrap_in_nester_back(str, charP);
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
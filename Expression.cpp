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

Exp_Tree::Exp_Node* Exp_Tree::Exp_Node::append_child(Exp_Node* _child)
{
	_child->set_parent(this);
	_child->set_used_ids(this, this->used_ids);
	if (!_child->id)
	{
		for (unsigned int id : *(this->used_ids))
			_child->id++;
		_child->id++;
		this->used_ids->push_back(_child->id);
	}
	this->children.push_back(_child);
	return _child;
}

void Exp_Tree::Exp_Node::create_nodes_from_exp(string exp)
{
	// TODO: COMPLETE THIS

	console << "building Node...";

	bool is_num_or_var = true;

	try {

		// (pemd)AS
		for (auto charP = exp.begin();
			charP != exp.end(); charP++)
		{
			// skip enclosed scope
			if (lib::char_in_arr(*charP, Expression::nestersOpen))
				charP = lib::find_closing(charP, exp);

			// Addition
			else if (*charP == '+' && charP > exp.begin())
			{
				string add1{ exp.begin(), charP };
				string add2{ charP + 1, exp.end() };

				this->append_child(new Add_Node{ add1, add2 });
				is_num_or_var = false;
			}
			// Subtraciton
			else if (*charP == '-' && charP > exp.begin())
			{
				string minuend{ exp.begin(), charP };
				string subtrahend{ charP + 1, exp.end() };

				this->append_child(new Sub_Node{ minuend, subtrahend });
				is_num_or_var = false;
			}
		}

		// PEMD(as)
		for (auto charP = exp.begin();
			charP != exp.end(); charP++)
		{
			if (lib::char_in_arr(*charP, Expression::nestersOpen))
			{
				string::iterator c = lib::find_closing(charP, exp);
				// skip enclosed scope
				if (*(c + 1) != '+' ||
					*(c + 1) != '-'  )
						charP = c;
			}

			// Division
			if (*charP == '/')
			{
				string dividend{ lib::find_opening(charP - 1, exp) + 1, charP - 1 };
				string divisor{ charP + 2, lib::find_closing(charP + 1, exp) };

				this->append_child(new Div_Node{ dividend, divisor });
				is_num_or_var = false;
			}
			else if (*charP == '*')
			{
				string mul1{ lib::find_opening(charP - 1, exp) + 1, charP - 1 };
				string mul2{ charP + 2, lib::find_closing(charP + 1, exp) };

				this->append_child(new Div_Node{ mul1, mul2 });
				is_num_or_var = false;
			}
			else if (*charP == '^')
			{

				is_num_or_var = false;
			}

			// TODO: if the first char is -, multiply by -1
		}
	}
	catch (std::out_of_range e) {

	}
	catch (lib::calc_exception e) {

	}

	if (is_num_or_var)
	{
		bool is_num = true;
		// TODO: check if the first character is number, but the rest aren't

		for (char c : exp)
			if (lib::char_in_arr(c, Expression::alphabet) ||
				lib::char_in_arr(c, Expression::alphabetUpper))
				is_num == false;

		if (is_num)
			this->append_child(new Num_Node{lib::to_double(exp)});
		else
			this->append_child(new Var_Node{ exp });
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
		if (lib::char_in_arr(*(begin + it), operators) &&
			*(begin + it) != '^' && it != 1 &&
			*(begin + it) != nester)
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
		if ((lib::char_in_arr(*(begin + it - 1), operators) ||
			lib::char_in_arr(*(begin + it - 1), nesters)) && //char_in_operators(*(begin + it - 1)) && 
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
			/*if (*charP == '+' && *(charP + 1) == '+')
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
			}*/

			// TODO: convert subtraction to negative addition in Node assignment
			//       perhaps even do the entire code above in node assignment?*/

			

			// EXPONENT "**": change to symbol "^"
			if (*charP == '*' && *(charP + 1) == '*')
				str.replace(charP, charP + 2, "^");

			/* insert MULTIPLICATION "*" when symbol not present
			   AND when MULTIPLICATION applicable
			*/
			// TODO: a letter after a number?
			if (charP > str.begin() && charP < str.end()-1)
			{
				if (*charP == '('                             ||
					lib::char_in_arr(*charP, alphabet)      ||
					lib::char_in_arr(*charP, alphabetUpper) ||
					lib::char_in_arr(*charP, numbers)       ||
					lib::char_in_arr(*charP, constants)     ||
					lib::char_in_arr(*charP, symbols)         )
						if (*(charP - 1) != '*' && *(charP - 1) == ')')
							charP = str.insert(charP, '*');

				if (*charP == ')'                             ||
					lib::char_in_arr(*charP, alphabet)      ||
					lib::char_in_arr(*charP, alphabetUpper) ||
					lib::char_in_arr(*charP, numbers)       ||
					lib::char_in_arr(*charP, constants)     ||
					lib::char_in_arr(*charP, symbols)         )
						if (*(charP + 1) != '*' && *(charP + 1) == '(')
							charP = str.insert(charP + 1, '*') - 1;
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

	console << '"' + str + '"';
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

// TODO: rearrantge these
const std::array<uint32_t, 11> Expression::operators = { //8
	'+', '-', '±', '*', '/', '^', '!', '%' ///*end*/, '|', '(', ')'
};
const std::array<uint32_t, 10> Expression::numbers = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};
const std::array<uint32_t, 6> Expression::constants = { // 4
	'e', 'π', 'φ', '∞' ///*end*/, '≥', '≤'
};
const std::array<uint32_t, 26> Expression::alphabet = { // e is in constants
	'a', 'b', 'c', 'd', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', 'ƒ' // function f
};
const std::array<uint32_t, 26> Expression::alphabetUpper = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
	'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
	'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};
const std::array<uint32_t, 6> Expression::symbols = {
	'Σ', 'Θ', '⌠', '⌡', '∫', '°'
};
const std::array<uint32_t, 7> Expression::nesters = {
	'(', '[', '{', ')', ']', '}', '|'
};
const std::array<uint32_t, 4> Expression::nestersOpen = {
	'(', '[', '{', '|'
};
const std::array<uint32_t, 4> Expression::nestersClose = {
	')', ']', '}', '|'
};
const std::array<uint32_t, 14> Expression::punctuation = {
	'\'', '"', '<', '≤', '>', '≥', '[', ']', '(', ')', '{', '}', '.', ','
};
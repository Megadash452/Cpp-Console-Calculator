﻿#include "Expression.h"
#include "Calc Exceptions.h"
#include "Console.h"

/// --- Expression Tree ---

Exp_Tree::Exp_Tree()
	: lib::Tree{ "Expression<>" },
	first_node(new Exp_Tree::Exp_Node),
	entry_node(first_node)
{}

Exp_Tree::Exp_Tree(string exp)
	: lib::Tree{ "Expression<" + exp + ">"},
	first_node(new Exp_Tree::Exp_Node{ exp }),
	entry_node(first_node)
{}

Exp_Tree::Exp_Tree(Exp_Tree& t)
	: lib::Tree{ t },
	first_node(t.first_node),
	entry_node(first_node)
{}

Exp_Tree::~Exp_Tree()
{
	delete this->first_node;
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

void Exp_Tree::simplify()
{
	auto a = this->first_node->attempt_collapse();
	this->first_node->append_to_buf();
}

string Exp_Tree::to_str()
{
	return string{};
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

Exp_Tree::Exp_Node::Exp_Node()
	: lib::Node{  }, has_var(false)
{}

Exp_Tree::Exp_Node::Exp_Node(string exp)
	: lib::Node{  }, has_var(false)
{
	if (exp != "")
		this->create_nodes_from_exp(exp);
}

Exp_Tree::Exp_Node::Exp_Node(Exp_Tree::Exp_Node& n)
	: lib::Node{ n }, has_var(false)
{
	// make a copy of each child (Node*)
	for (auto i = n.children.begin(); i != n.children.end(); i++)
		this->children.push_back(new Exp_Tree::Exp_Node{ **i });
}

Exp_Tree::Exp_Node::Exp_Node(Exp_Tree::Exp_Node* n)
	: lib::Node{ n }, has_var(false)
{
	// make a copy of each child (Node*)
	for (Exp_Tree::Exp_Node* child : n->children)
		this->children.push_back(new Exp_Tree::Exp_Node{ child });
}

Exp_Tree::Exp_Node::~Exp_Node() {
	for (Exp_Tree::Exp_Node* n : this->children)
		delete n;
}


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

Exp_Tree::Exp_Node* Exp_Tree::Exp_Node::create_nodes_from_exp(string exp)
{
	bool is_num_or_var = true;
	Exp_Node* rtrn_node = nullptr;

	// (pemd)AS
	for (auto charP = exp.end() - 1;;)
	{
		// skip enclosed scope
		if (lib::char_in_arr(*charP, Expression::nestersClose))
			charP = lib::find_opening(charP, exp);

		// Addition
		else if (*charP == '+' && charP > exp.begin())
		{
			string add1{ exp.begin(), charP };
			string add2{ charP + 1, exp.end() };

			/*rtrn_node =*/return this->append_child(new Add_Node{ add1, add2 });
			is_num_or_var = false;
			break;
		}
		// Subtraction
		else if (*charP == '-' && charP > exp.begin())
		{
			string minuend{ exp.begin(), charP };
			string subtrahend{ charP + 1, exp.end() };

			/*rtrn_node =*/return this->append_child(new Sub_Node{ minuend, subtrahend });
			is_num_or_var = false;
			break;
		}

		if (charP > exp.begin())
			charP--;
		else
			break;
	}

	// PEMD(as)
	for (auto charP = exp.begin();            // TODO: URGENT: fix operand only calculates itself, and does not leave room for another
		charP != exp.end(); charP++)          // TODO: make it reverse so it follows order of operations
	{
		// skip () only if there isnt a + or - on both sides
		if (lib::char_in_arr(*charP, Expression::nestersOpen))
		{
			string::iterator close = lib::find_closing(charP, exp);

			// keep curly brackets.
			if (charP > exp.begin() && close < exp.end() - 1) {       // ...(___)...
				if (!(*(charP - 1) == '+' || *(charP - 1) == '-') ||
					!(*(close + 1) == '+' || *(close + 1) == '-'))
					charP = close + 1;
			}
			else if (charP == exp.begin() && close < exp.end() - 1) { // (___)...
				if (!(*(close + 1) == '+' || *(close + 1) == '-'))
					charP = lib::find_closing(charP + 1, exp) + 1;
			}
			else if (charP > exp.begin() && close == exp.end() - 1) { // ...(___)
				if (!(*(charP - 1) == '+' || *(charP - 1) == '-'))
					charP = close;
			}
			else if (charP == exp.begin() && close == exp.end() - 1)  // (___)
				continue;
				//charP = lib::find_closing(charP + 1, exp);
		}

		// -- Division
		if (*charP == '/')
		{
			string dividend{ lib::find_opening(charP - 1, exp) + 1, charP - 1 };
			string divisor{ charP + 2, lib::find_closing(charP + 1, exp) };

			/*rtrn_node =*/return this->append_child(new Div_Node{ dividend, divisor });
			is_num_or_var = false;
		}
		// -- Multiplication
		else if (*charP == '*')
		{
			string mul1{ lib::find_opening(charP - 1, exp) + 1, charP - 1 };
			string mul2{ charP + 2, lib::find_closing(charP + 1, exp) };

			/*rtrn_node =*/return this->append_child(new Mul_Node{ mul1, mul2 });
			is_num_or_var = false;
		}
		// -- Exponent
		else if (*charP == '^')
		{
			string base{ lib::find_opening(charP - 1, exp) + 1, charP - 1 };
			string expo{ charP + 2, lib::find_closing(charP + 1, exp) };

			/*rtrn_node =*/return this->append_child(new Pow_Node{ base, expo });
			is_num_or_var = false;
		}

		// TODO: if the first char is -, multiply by -1
	}

	if (is_num_or_var)
	{
		bool is_num = true;
		//int num_base = 10;

		// remove pos or neg symbol
		if (exp[0] == '+' || exp[0] == '-')
			exp.erase(exp.begin());

		// determine if node will be a num or var
		if (!lib::char_in_arr(exp[0], Expression::numbers) &&
			exp[0] != '+' && exp[0] != '-')
			is_num = false;

		// check base
		/*if (exp[0] == '0')
			if (exp[1] == 'x') {
				num_base = 16;
			}
			else if (exp[1] == 'b') {
				num_base = 2;
			}*/
		
		if (is_num) for (char c : exp)
			if (c == '_') {
				is_num = false;
				break;
			}
			else if (lib::char_in_arr(exp[0], Expression::alphabet) ||
				lib::char_in_arr(exp[0], Expression::alphabetUpper) &&
				&c != (exp.begin() + 1)._Ptr)

			{
				is_num = false;
				break;
			}
			// maybe add more conditions?

		// if determined that the node will be a variable, check if it has a valid name
		if (lib::lower_case(exp) != "ans" && !is_num)
			if (exp[0] == '_')
				throw lib::syntax_error{ "first letter of variable{ c{11}[" + exp + "] } cannot be '_'" };

			else if (lib::char_in_arr(exp[0], Expression::numbers) ||
				lib::char_in_arr(exp[0], Expression::operators) ||
				lib::char_in_arr(exp[0], Expression::symbols))
					throw lib::syntax_error{ "first letter of variable{ c{11}[" + exp + "] } cannot be a number or symbol (see \"help\" for more information)" };

			else if (exp[1] != '_' && exp.size() > 1)
				throw lib::syntax_error{ "Variable name can only be one char (may be followed by '_' for subscript)" };

			else
				/*rtrn_node =*/return this->append_child(new Var_Node{ exp });

		else if (lib::lower_case(exp) == "ans" && !is_num)
			if (Expression::get_var("ans") != nullptr)
				/*rtrn_node =*/return this->append_child(Expression::get_var("ans")->exp_tree.first_node->children[0]);
			else
				throw lib::var_error{ "This is the first calculator entry, \"ans\" is not defined" };


		if (is_num)
			/*rtrn_node =*/return this->append_child(new Num_Node{lib::to_double(exp)});
		else
			/*rtrn_node =*/return this->append_child(new Var_Node{ exp });
	}

	return rtrn_node;
}

Exp_Tree::Num_Node* Exp_Tree::Exp_Node::attempt_collapse()
{
	Exp_Tree::Num_Node* a = this->children[0]->attempt_collapse();
	if (a != nullptr && a != this->children[0]) {
		delete this->children[0];
		this->children[0] = a;
	}
	return a;
}

void Exp_Tree::Exp_Node::append_to_buf()
{
	for (Exp_Tree::Exp_Node* child : this->children)
		child->append_to_buf();
}

/// -- Other Nodes

Exp_Tree::Nest_Node::Nest_Node(string n, char _type)
	: Exp_Tree::Exp_Node{  }, nest_type(_type)
{}


Exp_Tree::Op_Node::Op_Node(char _sign)
	: Exp_Tree::Exp_Node{  }, sign(_sign)
{}

// Exponent Node
Exp_Tree::Pow_Node::Pow_Node(string _base, string _exp)
	: Exp_Tree::Op_Node{ '^' }
{
	this->base = this->create_nodes_from_exp(_base);
	this->exp = this->create_nodes_from_exp(_exp);
}
Exp_Tree::Pow_Node::Pow_Node(Exp_Tree::Exp_Node* _base, Exp_Tree::Exp_Node* _exp)
	: Exp_Tree::Op_Node{ '^' }, base(_base), exp(_exp)
{}

Exp_Tree::Pow_Node::~Pow_Node()
{
	delete this->base;
	delete this->exp;
}

Exp_Tree::Num_Node* Exp_Tree::Pow_Node::attempt_collapse()
{
	Exp_Tree::Num_Node* a = this->base->attempt_collapse();
	Exp_Tree::Num_Node* b = this->exp->attempt_collapse();

	if (a != nullptr && a != this->base) {
		this->children[0] = a;
		delete base;
		this->base = a;
	}
	if (b != nullptr && b != this->exp) {
		this->children[1] = b;
		delete exp;
		this->exp = b;
	}

	if (a != nullptr && b != nullptr)
	{
		if (a->has_var || b->has_var)
			this->has_var = true;

		return new Exp_Tree::Num_Node{ pow(a->num, b->num) };
	}
	else
		return nullptr;
}

void Exp_Tree::Pow_Node::append_to_buf()
{
	Expression::buf << std::fixed
		<< std::setprecision(11);

	this->base->append_to_buf();
	Expression::buf << '^';
	this->exp->append_to_buf();
}


// Division Node
Exp_Tree::Div_Node::Div_Node(string _dividend, string _divisor)
	: Exp_Tree::Op_Node{ '/' }
{
	this->dividend = this->create_nodes_from_exp(_dividend);
	this->divisor = this->create_nodes_from_exp(_divisor);
}
Exp_Tree::Div_Node::Div_Node(Exp_Tree::Exp_Node* _dividend, Exp_Tree::Exp_Node* _divisor)
	: Exp_Tree::Op_Node{ '/' }, dividend(_dividend), divisor(_divisor)
{}

Exp_Tree::Div_Node::~Div_Node()
{
	delete this->dividend;
	delete this->divisor;
}

Exp_Tree::Num_Node* Exp_Tree::Div_Node::attempt_collapse()
{
	Exp_Tree::Num_Node* a = this->dividend->attempt_collapse();
	Exp_Tree::Num_Node* b = this->divisor->attempt_collapse();

	if (a != nullptr && a != this->dividend) {
		this->children[0] = a;
		delete dividend;
		this->dividend = a;
	}
	if (b != nullptr && b != this->divisor) {
		this->children[1] = b;
		delete divisor;
		this->divisor = b;
	}

	if (a != nullptr && b != nullptr)
	{
		if (a->has_var || b->has_var)
			this->has_var = true;

		return new Exp_Tree::Num_Node{ a->num / b->num };
	}
	else
		return nullptr;
}

void Exp_Tree::Div_Node::append_to_buf()
{
	Expression::buf << std::fixed
		<< std::setprecision(11);

	this->dividend->append_to_buf();
	Expression::buf << '/';
	this->divisor->append_to_buf();
}


// Multiplication Node
Exp_Tree::Mul_Node::Mul_Node(string _mul1, string _mul2)
	: Exp_Tree::Op_Node{ '*' }
{
	this->mul1 = this->create_nodes_from_exp(_mul1);
	this->mul2 = this->create_nodes_from_exp(_mul2);
}
Exp_Tree::Mul_Node::Mul_Node(Exp_Tree::Exp_Node* _mul1, Exp_Tree::Exp_Node* _mul2)
	: Exp_Tree::Op_Node{ '*' }, mul1(_mul1), mul2(_mul2)
{}

Exp_Tree::Mul_Node::~Mul_Node()
{
	delete this->mul1;
	delete this-> mul2;
}

Exp_Tree::Num_Node* Exp_Tree::Mul_Node::attempt_collapse()
{
	Exp_Tree::Num_Node* a = this->mul1->attempt_collapse();
	Exp_Tree::Num_Node* b = this->mul2->attempt_collapse();

	if (a != nullptr && a != this->mul1) {
		this->children[0] = a;
		delete mul1;
		this->mul1 = a;
	}
	if (b != nullptr && b != this->mul2) {
		this->children[1] = b;
		delete mul2;
		this->mul2 = b;
	}

	if (a != nullptr && b != nullptr)
	{
		if (a->has_var || b->has_var)
			this->has_var = true;

		return new Exp_Tree::Num_Node{ a->num * b->num };
	}
	else
		return nullptr;
}

void Exp_Tree::Mul_Node::append_to_buf()
{
	this->mul1->append_to_buf();
	Expression::buf << '*';
	this->mul2->append_to_buf();
}


// Subtraction Node
Exp_Tree::Sub_Node::Sub_Node(string _minuend, string _subtrahend)
	: Exp_Tree::Op_Node{ '-' }
{
	this->minuend = this->create_nodes_from_exp(_minuend);
	this->subtrahend = this->create_nodes_from_exp(_subtrahend);
}
Exp_Tree::Sub_Node::Sub_Node(Exp_Tree::Exp_Node* _minuend, Exp_Tree::Exp_Node* _subtrahend)
	: Exp_Tree::Op_Node{ '-' }, minuend(_minuend), subtrahend(_subtrahend)
{}

Exp_Tree::Sub_Node::~Sub_Node()
{
	delete this->minuend;
	delete this->subtrahend;
}

Exp_Tree::Num_Node* Exp_Tree::Sub_Node::attempt_collapse()
{
	Exp_Tree::Num_Node* a = this->minuend->attempt_collapse();
	Exp_Tree::Num_Node* b = this->subtrahend->attempt_collapse();

	if (a != nullptr && a != this->minuend) {
		this->children[0] = a;
		delete minuend;
		this->minuend = a;
	}
	if (b != nullptr && b != this->subtrahend) {
		this->children[1] = b;
		delete subtrahend;
		this->subtrahend = b;
	}

	if (a != nullptr && b != nullptr)
	{
		if (a->has_var || b->has_var)
			this->has_var = true;

		return new Exp_Tree::Num_Node{ a->num - b->num };
	}
	else
		return nullptr;
}

void Exp_Tree::Sub_Node::append_to_buf()
{
	this->minuend->append_to_buf();
	Expression::buf << '-';
	this->subtrahend->append_to_buf();
}


// Addition Node
Exp_Tree::Add_Node::Add_Node(string _add1, string _add2)
	: Exp_Tree::Op_Node{ '+' }
{
	this->add1 = this->create_nodes_from_exp(_add1);
	this->add2 = this->create_nodes_from_exp(_add2);
}
Exp_Tree::Add_Node::Add_Node(Exp_Tree::Exp_Node* _add1, Exp_Tree::Exp_Node* _add2)
	: Exp_Tree::Op_Node{ '+' }, add1(_add1), add2(_add2)
{}

Exp_Tree::Add_Node::~Add_Node()
{
	delete this->add1;
	delete this->add2;
}

Exp_Tree::Num_Node* Exp_Tree::Add_Node::attempt_collapse()
{
	Exp_Tree::Num_Node* a = this->add1->attempt_collapse();
	Exp_Tree::Num_Node* b = this->add2->attempt_collapse();

	if (a != nullptr && a != this->add1) {
		this->children[0] = a;
		delete add1;
		this->add1 = a;
	}
	if (b != nullptr && b != this->add2) {
		this->children[1] = b;
		delete add2;
		this->add2 = b;
	}

	if (a != nullptr && b != nullptr)
	{
		if (a->has_var || b->has_var)
			this->has_var = true;

		return new Exp_Tree::Num_Node{ a->num + b->num };
	}
	else
		return nullptr;
}

void Exp_Tree::Add_Node::append_to_buf()
{
	this->add1->append_to_buf();
	Expression::buf << '+';
	this->add2->append_to_buf();
}


// Num and var nodes
Exp_Tree::Num_Node::Num_Node(double _num)
	: Exp_Node{  }, num(_num), base(10)
{}

Exp_Tree::Num_Node* Exp_Tree::Num_Node::attempt_collapse()
{
	return this;
}

void Exp_Tree::Num_Node::append_to_buf()
{
	Expression::buf << std::fixed
		<< std::setprecision(lib::fractional_digits(this->num));

	Expression::buf << this->num;
}


Exp_Tree::Var_Node::Var_Node(string _var)
	: Exp_Node{  }, var(_var)
{
	this->has_var = true;
	Expression* e = Expression::get_var(var);
	if (e == nullptr)
		console.warn("Variable c{11}[" + var + "] is not defined.");
	else if (e->expression == "")
		console.warn("Variable c{11}[" + var + "] is not defined.");;
}

Exp_Tree::Num_Node* Exp_Tree::Var_Node::attempt_collapse()
{
	Expression* e = Expression::get_var(this->var);
	if (e != nullptr)
		if (e->exp_tree.first_node->children[0] != nullptr)
			return e->exp_tree.first_node->children[0]->attempt_collapse();
		else
			return nullptr;
	else
		return nullptr;
	
}

void Exp_Tree::Var_Node::append_to_buf()
{
	Expression::buf << this->var;
}

/// --- --- --- ---



/// --- Expression ---
std::map<string, Expression*> Expression::variables{
	{ "ans", nullptr },
	{ "e", new Expression{ "2.718281828" } },
	{ "π", new Expression{ "3.141592654" } },
	{ "φ", new Expression{ "1.61803398875" } }//,
	//{ "∞", new Expression{ "99999999999" } }
};

std::ostringstream Expression::buf{};

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
		if ((begin + it) == str.begin())
		{
			begin = str.insert(str.begin(), closer);
			break;
		}
		else if ((lib::char_in_arr(*(begin + it - 1), operators) ||
			lib::char_in_arr(*(begin + it - 1), nesters)) && //char_in_operators(*(begin + it - 1)) && 
			*(begin + it) != nester &&
			it != 0)
		{
			begin = str.insert(begin + it, closer) - it;
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
	for (auto it = str.begin(); it < str.end(); it++)
		if (*it == ' ' && it == str.end() - 1) {
			str.pop_back();
			break;
		}
		else if (*it == ' ')
			it = str.erase(it);


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

			

			// EXPONENT "**": change to symbol "^"
			if (*charP == '*' && *(charP + 1) == '*')
				str.replace(charP, charP + 2, "^");

			/* insert MULTIPLICATION "*" when symbol not present
			   AND when MULTIPLICATION applicable
			*/
			// TODO: a letter after a number?
			if (charP > str.begin() && *(charP - 1) == ')' && *charP != '*')
				if (*charP == '('                           ||
					lib::char_in_arr(*charP, alphabet)      ||
					lib::char_in_arr(*charP, alphabetUpper) ||
					lib::char_in_arr(*charP, numbers)       ||
					lib::char_in_arr(*charP, constants)     ||
					lib::char_in_arr(*charP, symbols)         )
						charP = str.insert(charP, '*');
				else;

			else if (charP < str.end() - 1 && *(charP + 1) == '(' && *charP != '*')
				if (*charP == ')'                           ||
					lib::char_in_arr(*charP, alphabet)      ||
					lib::char_in_arr(*charP, alphabetUpper) ||
					lib::char_in_arr(*charP, numbers)       ||
					lib::char_in_arr(*charP, constants)     ||
					lib::char_in_arr(*charP, symbols)         )
						charP = str.insert(charP + 1, '*') - 1;

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
			throw e;
			break;
		}
		catch (std::exception) {
			throw lib::syntax_error{ "Bad syntax around \"" + string(charP - 1, charP + 2) + "\"" };
			break;
		}
	}

	if (str[0] != '+' && str[0] != '-' && str != "")
			str = '+' + str;

	//console << '"' + str + '"' + '\n';
    return str;
}

string Expression::parseForPrint(string str)
{
	return str;
}

Expression& Expression::simplify()
{
	// empty the buffer
	Expression::buf.str("");
	Expression::buf.clear();

	this->exp_tree.simplify();
	this->expression = Expression::buf.str();

	// empty the buffer
	Expression::buf.str("");
	Expression::buf.clear();

	this->readExp = Expression::parseForRead(expression);

	return *this;
}

bool Expression::var_defined(string var)
{
	if (Expression::variables.find(var) == Expression::variables.end())
		return false;
	else
		return true;
}

void Expression::set_var(string varname, string exp)
{
	Expression* e = new Expression{ exp };
	e->simplify();
	Expression::set_var(varname, e);
}

void Expression::set_var(string varname, Expression* exp)
{
	if (varname[0] == '_')
		throw lib::syntax_error{ "first letter of variable{ c{11}[" + varname + "] } cannot be '_'" };

	else if (varname[1] != '_' && varname.size() > 1 && varname != "ans")
		throw lib::syntax_error{ "Variable names can only be one char (may be followed by '_' for subscript)" };

	else if (lib::char_in_arr(varname[0], numbers) ||
		lib::char_in_arr(varname[0], operators) ||
		lib::char_in_arr(varname[0], symbols))
		// TODO: add help info
		throw lib::syntax_error{ "first letter of variable {c{11}[" + varname + "]} cannot be a number or symbol (see \"help\" for more information)" };

	else if (varname.size() == 1 && lib::char_in_arr(varname[0], constants))
		// TODO: add help info
		throw lib::store_error{ "variable name {c{11}[" + varname + "]} cannot be a predifined constant (see \"help\" for more information)" };

	else if (lib::char_in_arr(varname[0], alphabet) ||
		lib::char_in_arr(varname[0], alphabetUpper))
	{
		if (Expression::var_defined(varname))
		{
			delete Expression::variables[varname];
			Expression::variables[varname] = exp;
		}
		else
			Expression::variables.insert(std::pair<string, Expression*>{ varname, exp });

		if (varname != "ans")
			console.log("c{11}[" + varname + "] = c{9}[" + exp->expression + ']');
	}
}

Expression* Expression::get_var(string varname)
{
	return Expression::variables[varname];
}

std::map<string, Expression*> Expression::get_vars()
{
	// make sure to call delete on each new ptr (heap allocated) after done with vars!
	std::map<string, Expression*> map;
	for (std::pair<string, Expression*> pair : Expression::variables)
		if (pair.second != nullptr)
			map.insert(std::pair<string, Expression*>{
				pair.first, new Expression{ *(pair.second) }
			});
		else
			map.insert(std::pair<string, Expression*>{
				pair.first, new Expression{}
			});
	return map;
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
const std::array<uint32_t, 5> Expression::symbols = {
	'Σ', 'Θ', '⌠', '⌡', '∫'//, '°'
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
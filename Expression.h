#pragma once
#include "Utils.h"
#include "Calc Exceptions.h"
#include "Tree.h"
#include "Console.h"

struct Exp_Tree : public lib::Tree
{
	struct Exp_Node;  // Overall parent Node
	//struct Func_Node; // Function Node
	struct Nest_Node; // Nester Node (parenthesis, set, abs-val, etc.)
	struct Op_Node;   // Operation Node
		struct Pow_Node;  // Exponent Node
		struct Div_Node;  // Division Node
		struct Mul_Node;  // Multiplication Node
		//struct Sub_Node;  // Subtraction Node (do addition with negative number instead)
		struct Add_Node;  // Addition Node
	struct Num_Node;  // Number Node (double)
	struct Var_Node;  // Variable Node


	Exp_Tree();
	Exp_Tree(string exp);
	Exp_Tree(Exp_Tree&);


	// Overall parent Node
	struct Exp_Node : public lib::Node
	{
		Exp_Node()
			: lib::Node{   } {}
		Exp_Node(string exp)
			: lib::Node{ }
		{
			this->create_nodes_from_exp(exp);
		}
		Exp_Node(Exp_Tree::Exp_Node& n)
			: lib::Node{ n } {}
		Exp_Node(Exp_Tree::Exp_Node* n)
			: lib::Node{ n } {}

		std::vector<Exp_Node*> children;
		//Exp_Node* append_child(Exp_Node* _child);
		void create_nodes_from_exp(string exp);

		const string node_type = "null";
	};

	// Nester Node (parenthesis, set, abs-val, etc.)
	struct Nest_Node : public Exp_Node
	{
		Nest_Node(string n, char _type)
			: Exp_Node{  }, nest_type(_type)
		{}
		char nest_type;
		const string node_type = "Nester Node";
	};

	// Operation Node
	struct Op_Node : public Exp_Node
	{
		Op_Node(char _sign)
			: Exp_Node{  }, sign(_sign)
		{console << this->sign; }
		char sign;

		const string node_type = "Operation Node";
	};
	// Operation Nodes
		// Exponent Node
		struct Pow_Node : public Op_Node
		{
			Pow_Node(Exp_Tree::Exp_Node* _base, Exp_Tree::Exp_Node* _exp)
				: Op_Node{ '^' }, base(_base), exp(_exp)
			{}
			const string node_type = "Division Node";

			Exp_Tree::Exp_Node* base; // number being divided
			Exp_Tree::Exp_Node* exp; // number dividing

		};
		// Division Node
		struct Div_Node : public Op_Node
		{
			Div_Node(Exp_Tree::Exp_Node* _dividend, Exp_Tree::Exp_Node* _divisor)
				: Op_Node{ '/' }, dividend(_dividend), divisor(_divisor)
			{}
			Div_Node(string _dividend, string _divisor)
				: Op_Node{ '/' }
			{
				this->dividend = this->append_child(new Exp_Node{ _dividend });
				this->divisor = this->append_child(new Exp_Node{ _divisor });
			}
			const string node_type = "Division Node";

			Exp_Tree::Exp_Node* dividend; // number being divided
			Exp_Tree::Exp_Node* divisor; // number dividing
			
		};
		// Multiplication Node
		struct Mul_Node : public Op_Node
		{
			Mul_Node(Exp_Tree::Exp_Node* n1, Exp_Tree::Exp_Node* n2)
				: Op_Node{ '*' }, mul1(n1), mul2(n2)
			{}
			const string node_type = "Multipliaction Node";

			Exp_Tree::Exp_Node* mul1;
			Exp_Tree::Exp_Node* mul2;
		};
		// Subtraction Node (do addition with negative number instead)
		/*struct Sub_Node : public Op_Node
		{
			Sub_Node()
				: Op_Node{ '-' }
			{}
			const string node_type = "Subtraction Node";

			Exp_Tree::Exp_Node* sub;
		};*/
		// Addition Node
		struct Add_Node : public Op_Node
		{
			Add_Node(Exp_Tree::Exp_Node* n1, Exp_Tree::Exp_Node* n2)
				: Op_Node{ '+' }, add1(n1), add2(n2)
			{}
			const string node_type = "Addition Node";

			Exp_Tree::Exp_Node* add1;
			Exp_Tree::Exp_Node* add2;
		};
	// ---

	// Number Node (double)
	struct Num_Node : public Exp_Node
	{
		Num_Node(int _num)
			: Exp_Node{  }, num(_num)
		{}
		int num;
		const string node_type = "Number Node";
	};

	// Variable Node
	struct Var_Node : public Exp_Node
	{
		Var_Node(char _var)
			: Exp_Node{  }
		{
			this->var = _var;
		}
		string var;
		const string node_type = "Variable Node";
	};


	void create_nodes_from_exp(string exp);
	void reset_nodes(string exp);

	Exp_Tree::Exp_Node* first_node;
	Exp_Tree::Exp_Node*& entry_node;

	//void operator =(Exp_Tree&);
};

class Expression
{
private:
	string readExp;
	// helpers
	//static string::iterator wrap_in_nester(string& str, string::iterator begin, string::iterator end, char nester = '(');
	static string::iterator wrap_in_nester_forward(string& str, string::iterator begin, char nester = '(');
	static string::iterator wrap_in_nester_back(string& str, string::iterator begin  , char nester = ')');
public:
	Expression();
	Expression(Expression&);
	Expression(string);

	static string parseForRead(string);
	static string parseForPrint(string);

	Expression& simplify();

	string expression;
	Exp_Tree exp_tree;
};
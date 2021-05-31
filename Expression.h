#pragma once
#include <array>

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
			// TODO: define type for each class after this constructor is done
		}
		Exp_Node(Exp_Tree::Exp_Node& n)
			: lib::Node{ n } {}
		Exp_Node(Exp_Tree::Exp_Node* n)
			: lib::Node{ n } {}

		std::vector<Exp_Node*> children;
		Exp_Node* append_child(Exp_Node* _child);
		void create_nodes_from_exp(string exp);
		virtual string type() { return this->node_type; }

	protected: string node_type = "null";
	};

	// Nester Node (parenthesis, set, abs-val, etc.)
	struct Nest_Node : public Exp_Node
	{
		Nest_Node(string n, char _type)
			: Exp_Node{  }, nest_type(_type)
		{}
		char nest_type;
	protected: string node_type = "Nester Node";
	};

	// Operation Node
	struct Op_Node : public Exp_Node
	{
		Op_Node(char _sign)
			: Exp_Node{  }, sign(_sign)
		{console << this->sign; }
		char sign;

	protected: string node_type = "Operation Node";
	};
	// Operation Nodes
		// Exponent Node
		struct Pow_Node : public Op_Node
		{
			Pow_Node(Exp_Tree::Exp_Node* _base, Exp_Tree::Exp_Node* _exp)
				: Op_Node{ '^' }, base(_base), exp(_exp)
			{}
			Pow_Node(string _base, string _exp)
				: Op_Node{ '^' }
			{
				this->base = this->append_child(new Exp_Node{ _base });
				this->exp = this->append_child(new Exp_Node{ _exp });
			}
		
			Exp_Tree::Exp_Node* base; // number being divided
			Exp_Tree::Exp_Node* exp; // number dividing

		protected: string node_type = "Division Node";
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
			
			Exp_Tree::Exp_Node* dividend; // number being divided
			Exp_Tree::Exp_Node* divisor; // number dividing

		protected: string node_type = "Division Node";
		};
		// Multiplication Node
		struct Mul_Node : public Op_Node
		{
			Mul_Node(Exp_Tree::Exp_Node* _mul1, Exp_Tree::Exp_Node* _mul2)
				: Op_Node{ '*' }, mul1(_mul1), mul2(_mul2)
			{}
			Mul_Node(string _mul1, string _mul2)
				: Op_Node{ '*' }
			{
				this->mul1 = this->append_child(new Exp_Node{ _mul1 });
				this->mul2 = this->append_child(new Exp_Node{ _mul2 });
			}
		
			Exp_Tree::Exp_Node* mul1;
			Exp_Tree::Exp_Node* mul2;

		protected: string node_type = "Multipliaction Node";
		};
		// Subtraction Node (do addition with negative number instead)
		struct Sub_Node : public Op_Node
		{
			Sub_Node(Exp_Tree::Exp_Node* _minuend, Exp_Tree::Exp_Node* _subtrahend)
				: Op_Node{ '-' }, minuend(_minuend), subtrahend(_subtrahend)
			{}
			Sub_Node(string _minuend, string _subtrahend)
				: Op_Node{ '-' }
			{
				this->minuend = this->append_child(new Exp_Node{ _minuend });
				this->subtrahend = this->append_child(new Exp_Node{ _subtrahend });
			}
			
			Exp_Tree::Exp_Node* minuend; // number being subtracted
			Exp_Tree::Exp_Node* subtrahend; // number subtrahend is subtracted from
			// e.g.:     1     -      2
			//       (minuend)   (subtrahend)

		protected: string node_type = "Subtraction Node";
		};
		// Addition Node
		struct Add_Node : public Op_Node
		{
			Add_Node(Exp_Tree::Exp_Node* _add1, Exp_Tree::Exp_Node* _add2)
				: Op_Node{ '+' }, add1(_add1), add2(_add2)
			{}
			Add_Node(string _add1, string _add2)
				: Op_Node{ '+' }
			{
				this->add1 = this->append_child(new Exp_Node{ _add1 });
				this->add2 = this->append_child(new Exp_Node{ _add2 });
			}
		
			Exp_Tree::Exp_Node* add1;
			Exp_Tree::Exp_Node* add2;

		protected: string node_type = "Addition Node";
		};
	// ---

	// Number Node (double)
	struct Num_Node : public Exp_Node
	{
		Num_Node(double _num)
			: Exp_Node{  }, num(_num)
		{}
		double num;
	protected: string node_type = "Number Node";
	};

	// Variable Node
	struct Var_Node : public Exp_Node
	{
		Var_Node(string _var)
			: Exp_Node{  }
		{
			this->var = _var;
		}
		string var;
	protected: string node_type = "Variable Node";
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

	static const std::array<uint32_t, 11> operators;
	static const std::array<uint32_t, 10> numbers;
	static const std::array<uint32_t, 6> constants;
	static const std::array<uint32_t, 26> alphabet;
	static const std::array<uint32_t, 26> alphabetUpper;
	static const std::array<uint32_t, 6> symbols;
	static const std::array<uint32_t, 7> nesters;
	static const std::array<uint32_t, 4> nestersOpen;
	static const std::array<uint32_t, 4> nestersClose;
	static const std::array<uint32_t, 14> punctuation;
};
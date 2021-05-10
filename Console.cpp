#include "Console.h"

string Console::Keywords[30] = {"null", "true", "false", "console", "term", "expression", "function", "func"
                               "bool", "char", "int", "string", "str", "array", "arr", "map",

                               "add", "subtract", "multiply", "divide", "plus", "minus",
                               "addition", "subtraction", "multiplication", "division",
                               "derivative", "integral",
                               "derive", "integrate"};

Console::Console()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(this->handle, 7);
	this->node_indent = 0;

	this->margin_size = 0;
	this->border_size = 1;
	this->padding_size = 2;

	this->text_area_width = 75;
	this->text_area_height = 75;

	this->width = this->border_size * 2 + this->padding_size * 2 + this->text_area_width;
	this->height = 1 + this->border_size * 2 + this->padding_size * 2 + this->text_area_height;

	assert(this->padding_size >= 2);
}

void Console::log(string msg, int color, bool new_line)
{
	/* Concatenate in msg by std::string. {<<} operator will come later on.
	*/

	std::cout << "║  ";

	this->set_color(color);

	int chars_printed = 0;
	for (string::iterator
		charP = msg.begin();
		charP != msg.end();
		charP++)
	{
		if (*charP == '\n')
		{
			this->new_line();
			continue;
		}
			

		if (*charP == 'c' && *(charP + 1) == '{')
		{
			string tempStr;
			for (string::iterator i = charP + 2; *i != '}'; i++)
			{
				tempStr.push_back(*i);
				if (*(i + 1) == '}')
					charP = i + 2;
			}
			this->color_by_delim(charP, stoi(tempStr));
		}
		if (charP >= msg.end())
			break;

		// TODO: Add keyword syntax highlight
		try {
			if (*charP == '"')
				color_by_delim(charP, 2, true);
			else if (*charP == '\'' && *(charP + 2) == '\'')
				color_by_delim(charP, 3, true);
			else if (*charP == '<')
				color_by_delim(charP, 11, true);
			else if (charP + 1 < msg.end())
				if (*charP == ' ' && char_in_numbers(*(charP + 1)))
				{
					bool valid = true;
					for (auto it = charP + 1; it < msg.end(); it++)
						if (!char_in_numbers(*it))
							valid = false;
					if (valid) color_by_delim(charP, 9, true);
				}

			if (charP >= msg.end()) break;
		}
		catch (std::out_of_range) {

		}
		
		std::cout << *charP;
		chars_printed++;
		// TODO: close the right borders when printing new line
		if (chars_printed >= this->text_area_width)
			std::cout << 
	}
	if (new_line)
		std::cout << std::endl;
	if (color)
		this->set_color(this->default_color);
}

//void Console::log(lib::Tree tree) { this->log_tree(tree); }

//string Console::input(string msg)
//{
//	this->log(msg);
//	string t;
//	string& temp = t;
//	this->input(temp);
//	return string();
//}
void Console::input(string& var)
{
	std::cout << "║  --> ";
	this->set_color(8);
	getline(std::cin, var);
	this->reset_color();
}
void Console::input(int& var)
{
	std::cout << "║  --> ";
	this->set_color(8);
	std::cin >> var;
	this->reset_color();
}


void Console::error(string error) {
	this->log("c{4}[-- Error --] " + error);
}
void Console::error(lib::calc_exception& e)
{
	this->log("c{4}[-- " + e.type() + " --] " + string{e.what()});
}
void Console::warn(string warning) {
	this->log("c{6}[--Warning--] " + warning);
}


void Console::log_node(lib::Node* node, bool prnt_chldrn)
{
	std::cout << "║  ";

	// Apply indent
	for (int i = 0; i < this->node_indent; i++)
		std::cout << " ";

	this->log_ptr(node);
	this->set_color(11);
	if (node != nullptr)
		std::cout << "<" << node->id << ">";
	else
		std::cout << "<NULL>";
	this->set_color(0);
	std::cout << ": {" << std::endl;
	
	// print child nodes with indent
	this->node_indent += 4;
	if (prnt_chldrn && node)
		for (lib::Node* child : node->children)
			this->log_node(child);
	this->node_indent -= 4;

	this->log("", 0, false);

	// Apply indent
	for (int i = 0; i < this->node_indent; i++)
		std::cout << " ";

	std::cout << "}" << std::endl;
}
void Console::log_tree(const lib::Tree& tree)
{
	this->log(tree.name + "c{0}[:] c{10}[--v]", GREEN);
	this->log_node(tree.first_node);
	this->log("^-- " + tree.name, GREEN);
}

/// -- Inline Logs --

void Console::log_ptr(const void* ptr)
{
	this->set_color(MAGENTA);
	std::cout << "*0x" << ptr << '*';
	this->set_color(COLOR_DEFAULT);
}
void Console::log_str(string str)
{
	this->set_color(DARK_GREEN);
	std::cout << '\"' << str << '\"';
	this->set_color(COLOR_DEFAULT);
}
void Console::log_char(char c)
{
	this->set_color(DARK_CYAN);
	std::cout << "'" << c << "'";
	this->set_color(COLOR_DEFAULT);
}
void Console::log_int(int i)
{
	this->set_color(BLUE);
	std::cout << i;
	this->set_color(COLOR_DEFAULT);
}

/*void Console::log(std::vector<const char*> vect)
{
	std::cout << "|  string";
	this->set_color(15);
	std::cout << "[] { ";

	for (std::vector<const char*>::iterator
		strP = vect.begin();
		strP != vect.end();
		strP++)
	{
		this->set_color(2);
		std::cout << "\"" << *strP << "\"";
		this->set_previous_color();
		std::cout << ", ";
	}
	std::cout << "\b\b";
	std::cout << " };\n";
	this->set_color(7);
}*/
void Console::log(std::vector<string> vect)
{
	std::cout << "║  string";
	this->set_color(15);
	std::cout << '[';

	for (std::vector<string>::iterator
		strP = vect.begin();
		strP != vect.end();
		strP++)
	{
		this->log_str(*strP);
		std::cout << ", ";
	}
	this->set_color(15);
	std::cout << "\b\b";
	std::cout << "]\n";
	this->set_color(this->default_color);
}
void Console::log(std::vector<char> vect)
{
	std::cout << "║  char";
	this->set_color(15);
	std::cout << '[';

	for (std::vector<char>::iterator
		charP = vect.begin();
		charP != vect.end();
		charP++)
	{
		this->log_char(*charP);
		std::cout << ", ";
	}
	this->set_color(15);
	std::cout << "\b\b";
	std::cout << "]\n";
	this->set_color(this->default_color);
}
void Console::log(std::vector<int> vect)
{
	std::cout << "║  int";
	this->set_color(15);
	std::cout << '[';

	for (std::vector<int>::iterator
		intP = vect.begin();
		intP != vect.end();
		intP++)
	{
		this->log_int(*intP);
		std::cout << ", ";
	}
	this->set_color(15);
	std::cout << "\b\b";
	std::cout << "]\n";
	this->set_color(this->default_color);
}


void Console::set_color(int color)
{
	if (color)
	{
		this->previous_color = text_color;
		SetConsoleTextAttribute(this->handle, color);
		this->text_color = color;
	}
	else
	{
		this->previous_color = text_color;
		SetConsoleTextAttribute(this->handle, default_color);
		this->text_color = default_color;
	}
}
void Console::set_previous_color() {set_color(this->previous_color);}
void Console::reset_color(){set_color(0);}

void Console::color_by_delim(string::iterator& charP, int color, bool keep_delims) // Before using, make sure that the string::iterator is in this->closeDelims map;
{
	string::iterator delimP = charP;
	string::iterator closeTarget = lib::find_closing(delimP);

	if (lib::closeDelims[*delimP])
	{
		if (!keep_delims)
			charP++;

		this->set_color(color);
		if (keep_delims)
		{
			for (; charP != closeTarget;
				charP++)
				std::cout << *charP;
			std::cout << *charP;
		}
		else
			for (; charP != closeTarget;
				charP++)
				std::cout << *charP;
		charP++;
		this->set_previous_color();
	}
	else
	{
		for (; *charP != ' ' ||
			charP == delimP;
			charP++)
			std::cout << *charP;
		this->set_color(4);
		std::cout << "<-(error applying color)";
		this->set_previous_color();
		std::cout << *charP;
	}
}
void Console::iterate_for_keywords(string::iterator& charP)
{
}

Console console;
#include "Console.h"
#include "Utils.h"
#include "Tree.h"

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
	this->chars_printed = 0;

	this->node_indent = 0;

	this->margin_size = 0;
	this->border_size = 1;
	this->padding_size = 2;

	this->text_area_width = 74;
	this->text_area_height = 75;

	this->width = this->border_size * 2 + this->padding_size * 2 + this->text_area_width;
	this->height = 1 + this->border_size * 2 + this->padding_size * 2 + this->text_area_height;

	//this->padding_size >= 2;
	// DO NOT call this->log(), this->color_by_delims(), or access openDelims/closeDelims here.
}

void Console::log(string msg, int color, bool new_line)
{
	/* Concatenate in msg by std::string. {<<} operator will come later on.
	*/

	/*std::cout << "║";
	this->apply_padding();*/

	this->set_color(color);

	for (string::iterator
		charP = msg.begin();
		charP != msg.end();
		charP++)
	{
		if (*charP == '\n' ||
			this->chars_printed >= this->text_area_width)
		{
			this->new_line();
			this->chars_printed = 0;
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
			continue;
		}
		if (charP >= msg.end())
			break;

		// TODO: Add keyword syntax highlight
		try {
			if (*charP == '"') {
				color_by_delim(charP, 2, true);
				continue;
			}
			else if (*charP == '\'' && *(charP + 2) == '\'') {
				color_by_delim(charP, 3, true);
				continue;
			}
			else if (*charP == '<') {
				color_by_delim(charP, 11, true);
				continue;
			}
			else if (charP + 1 < msg.end())
				if (*charP == ' ' && char_in_numbers(*(charP + 1)))
				{
					bool valid = true;
					for (auto it = charP + 1; it < msg.end(); it++)
						if (!char_in_numbers(*it))
							valid = false;
					if (valid) {
						color_by_delim(charP, 9, true);
						continue;
					}
				}
		}
		catch (std::out_of_range) {

		}
		
		std::cout << *charP;
		this->chars_printed++;
	}

	if (color)
		this->set_color(this->default_color);

	if (new_line)
		this->new_line();
}

void Console::log(string msg, bool new_line)
{
	this->log(msg, 0, new_line);
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
	std::cout << "--> ";
	this->hprint(4);

	this->set_color(8);
	auto pos = this->get_cursor_pos();
	getline(std::cin, var);
	int length = var.size();
	this->reset_color();

	this->set_cursor_pos(pos[0] + length, pos[1]);
	this->hprint(length);
	this->new_line();
}
void Console::input(int& var)
{
	std::cout << "--> ";
	this->hprint(4);

	this->set_color(8);
	auto pos = this->get_cursor_pos();
	std::cin >> var;
	int length = lib::digits(var);
	this->reset_color();

	this->set_cursor_pos(pos[0] + length, pos[1]);
	this->hprint(length);
	this->new_line();
}


void Console::error(string error) {
	this->log("c{4}[-- Error --] " + error);
}
void Console::error(lib::calc_exception& e)
{
	this->log("c{4}[-- " + e.type() + " --] " + string{e.what()});
}
void Console::warn(string warning) {
	this->log("c{6}[-- Warning --] " + warning);
}


void Console::log_node(lib::Node* node, bool prnt_chldrn)
{
	/*std::cout << "║";
	this->apply_padding();*/

	// Apply indent
	for (int i = 0; i < this->node_indent; i++)
	{
		std::cout << ' ';
		this->hprint();
	}
		

	this->log_ptr(node);
	this->set_color(11);
	if (node != nullptr) {
		std::cout << "<" << node->id << ">";
		this->hprint(lib::digits(node->id)+2);
	}
	else {
		std::cout << "<NULL>";
		this->hprint(6);
	}
	this->set_previous_color();
	std::cout << ": {";
	this->hprint(3);
	this->new_line();
	
	// print child nodes with indent
	this->node_indent += 4;
	if (prnt_chldrn && node)
		for (lib::Node* child : node->children)
			this->log_node(child);
	this->node_indent -= 4;

	this->log("", 0, false);

	// Apply indent
	for (int i = 0; i < this->node_indent; i++)
	{
		std::cout << " ";
		this->hprint();
	}
		

	std::cout << "}";
	this->hprint();
	this->new_line();
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
	this->hprint(SYS_PTR_DIGITS + 4);
	this->set_color(COLOR_DEFAULT);
}
void Console::log_str(string str)
{
	this->set_color(DARK_GREEN);
	std::cout << '\"' << str << '\"';
	for (char c : str)
		this->hprint();

	this->hprint(2);
	this->set_color(COLOR_DEFAULT);
}
void Console::log_char(char c)
{
	this->set_color(DARK_CYAN);
	std::cout << "'" << c << "'";
	this->hprint(3);
	this->set_color(COLOR_DEFAULT);
}
void Console::log_int(int i)
{
	this->set_color(BLUE);
	std::cout << i;
	this->hprint();
	this->set_color(COLOR_DEFAULT);
}

void Console::log_dbl(double d)
{
	this->set_color(BLUE);
	std::cout << d;
	this->hprint();
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
	// TODO: functional padding
	std::cout << "string";
	this->set_color(15);
	std::cout << '[';
	this->hprint(7);

	for (std::vector<string>::iterator
		strP = vect.begin();
		strP != vect.end();
		strP++)
	{
		this->log_str(*strP);
		std::cout << ", ";
		this->hprint(2);
	}
	this->set_color(15);
	std::cout << "\b\b";
	std::cout << "]";
	this->hprint();
	this->set_color(this->default_color);

	this->new_line();
}
void Console::log(std::vector<char> vect)
{
	// TODO: functional padding
	std::cout << "char";
	this->set_color(15);
	std::cout << '[';
	this->hprint(5);

	for (std::vector<char>::iterator
		charP = vect.begin();
		charP != vect.end();
		charP++)
	{
		this->log_char(*charP);
		std::cout << ", ";
		this->hprint(2);
	}
	this->set_color(15);
	std::cout << "\b\b";
	std::cout << "]";
	this->hprint();
	this->set_color(this->default_color);

	this->new_line();
}
void Console::log(std::vector<int> vect)
{
	// TODO: functional padding
	std::cout << "int";
	this->set_color(15);
	std::cout << '[';
	this->hprint(4);

	for (std::vector<int>::iterator
		intP = vect.begin();
		intP != vect.end();
		intP++)
	{
		this->log_int(*intP);
		std::cout << ", ";
		this->hprint(2);
	}
	this->set_color(15);
	std::cout << "\b\b";
	std::cout << "]";
	this->hprint();
	this->set_color(this->default_color);

	this->new_line();
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
	string::iterator closeTarget{};
	try {
		closeTarget = lib::find_closing(delimP);
	}
	catch (std::out_of_range) {
		return;
	}

	if (lib::closeDelims[*delimP])
	{
		if (!keep_delims)
			charP++;

		this->set_color(color);
		if (keep_delims)
		{
			for (; charP != closeTarget; charP++)
			{
				std::cout << *charP;
				this->hprint();
			}
			std::cout << *charP;
			this->hprint();
		}
		else
			for (; charP != closeTarget; charP++)
			{
				std::cout << *charP;
				this->hprint();
			}
		this->set_previous_color();
	}
	else
	{
		for (; *charP != ' ' ||
			charP == delimP;
			charP++)
		{
			std::cout << *charP;
			this->hprint();
		}
		this->set_color(4);
		std::cout << "<-(error applying color)";
		this->hprint(24);

		this->set_previous_color();
		std::cout << *charP;
		this->hprint();
	}
}
void Console::iterate_for_keywords(string::iterator& charP)
{
}

std::vector<int> Console::get_cursor_pos()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&csbi
		)
	)   return std::vector<int>{ -1, -1 };
	
	return std::vector<int>{ csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
}

void Console::set_cursor_pos(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::set_cursor_pos(std::vector<int> pos)
{
	this->set_cursor_pos(pos[0], pos[1]);
}

void Console::initializer_print()
{
	// string printed can only be 75 chars long (81-3-3)
	std::cout << "                           ╔═════════════════════════╗                          \n";
	std::cout << "╔══════════════════════════╣ Command Line Calculator ╠═════════════════════════╗\n";
	std::cout << "║                          ╚═════════════════════════╝                         ║\n";
	std::cout << "║  ";                                                                        //║\n";
	auto cpos = this->get_cursor_pos();  std::cout << '\n';                                    //║\n";
	std::cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";

	this->set_cursor_pos(cpos);

	this->log("\nWhat do you want to do? (type \"help\" or \"h\" to see your options)");
	this->log("---------------------------------------------------------------------------");
}

Console& Console::operator<<(string msg)
{
	console.log(msg);
	return *this;
}

Console& Console::operator<<(const char* msg)
{
	this->log(string{ msg });
	return *this;
}

Console& Console::operator<<(char c)
{
	this->log_char(c);
	return *this;
}

Console& Console::operator<<(int i)
{
	this->log_int(i);
	return *this;
}

Console& Console::operator<<(double d)
{
	this->log_dbl(d);
	return *this;
}

Console& Console::operator<<(std::vector<string> vect)
{
	this->log(vect);
	return *this;
}

Console& Console::operator<<(std::vector<char> vect)
{
	this->log(vect);
	return *this;
}

Console& Console::operator<<(std::vector<int> vect)
{
	this->log(vect);
	return *this;
}

Console& Console::operator<<(const void* ptr)
{
	this->log_ptr(ptr);
	return *this;
}

Console& Console::operator<<(lib::Tree tree)
{
	this->log_tree(tree);
	return *this;
}

Console& Console::operator<<(lib::Node* node)
{
	this->log_node(node);
	return *this;
}



void Console::hprint(int printed)
{ // Handles printing a character
	this->chars_printed += printed;
	if (this->chars_printed >= this->text_area_width)
	{
		this->new_line();
		this->chars_printed = 0;
	}
}

void Console::new_line()
{
	this->set_color(0);

	/*for (; this->chars_printed < this->text_area_width; this->chars_printed++)
		std::cout << ' ';
	this->apply_padding();*/

	this->set_cursor_pos(
		this->padding_size * 2 + this->text_area_width+1,
		this->get_cursor_pos()[1]
	);
	std::cout << "║\n║";
	this->chars_printed = 0;
	this->apply_padding();

	auto pos = this->get_cursor_pos();
	// this->closing_statement();
	std::cout << "\n╚══════════════════════════════════════════════════════════════════════════════╝";

	this->set_cursor_pos(pos);
	for (int i=0; i < this->text_area_width; i++)
		std::cout << ' ';
	this->apply_padding();
	std::cout << "║";
	this->set_cursor_pos(pos);
}
void Console::apply_padding()
{
	for (int i = 0; i < this->padding_size; i++)
		std::cout << ' ';
}


Console console{};
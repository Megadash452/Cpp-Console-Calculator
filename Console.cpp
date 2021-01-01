#include "Console.h"

Console::Console()
{
	SetConsoleTextAttribute(this->handle, 7);
}

void Console::log(string msg, int color)
{
	this->set_color(color);

	bool on_str = false;
	bool on_char = false;
	bool on_int = false;

	bool reset = false;

	std::cout << "|  ";
	for (string::iterator
		 charP = msg.begin();
		 charP != msg.end();
		 charP++)
	{
		if (*charP == '"' && !on_str)
		{
			this->set_color(2);
			on_str = true;
		}
		else if (*charP == '"' && on_str)
		{
			reset = true;
			on_str = false;
		}

		else if (*charP == '\'' && !on_char && !on_str)
		{
			this->set_color(3);
			on_char = true;
		}
		else if (*charP == '\'' && on_char && !on_str)
		{
			reset = true;
			on_char = false;
		}

		else if (char_in_numbers(*charP) && !on_int)
		{

		}
		std::cout << *charP;
		if (reset)
		{
			this->set_previous_color();
			reset = false;
		}
	}
	std::cout << std::endl;
	
}

void Console::log_str(string str)
{
	this->set_color(2);
	std::cout << "\"" << str << "\"";
	this->set_color(0);
}

void Console::log_char(char c)
{
	this->set_color(3);
	std::cout << "'" << c << "'";
	this->set_color(0);
}

void Console::log_int(int i)
{
	this->set_color(9);
	std::cout << i;
	this->set_color(0);
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
	std::cout << "|  string";
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
	std::cout << "|  char";
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
	std::cout << "|  int";
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
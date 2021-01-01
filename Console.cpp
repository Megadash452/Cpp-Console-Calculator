#include "Console.h"

Console::Console()
{
	SetConsoleTextAttribute(this->handle, 7);
}

void Console::log(string msg)
{
	std::cout << "|  " << msg << std::endl;
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
		this->set_color(2);
		std::cout << "\"" << *strP << "\"";
		this->set_color(0);
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
		this->set_color(3);
		std::cout << "'" << *charP << "'";
		this->set_color(0);
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
		this->set_color(9);
		std::cout << *intP;
		this->set_color(0);
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
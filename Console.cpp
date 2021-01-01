#include "Console.h"

Console::Console()
{
	
}

void Console::log(const char* msg)
{
	std::cout << msg << std::endl;
}
void Console::log(std::vector<string> vect)
{
	std::cout << "|  vector<string> { ";

	for (std::vector<string>::iterator
		strP = vect.begin();
		strP != vect.end();
		strP++)
	{
		this->set_color(2);
		std::cout << "\"" << *strP << "\"";
		this->reset_color();
	    std::cout << ", ";
	}
	std::cout << "\b\b";
	std::cout << " };\n";
}
void Console::log(std::vector<char> vect)
{
	std::cout << "|  vector<string> { ";

	for (std::vector<char>::iterator
		charP = vect.begin();
		charP != vect.end();
		charP++)
	{
		this->set_color(3);
		std::cout << "\"" << *charP << "\"";
		this->reset_color();
		std::cout << ", ";
	}
	std::cout << "\b\b";
	std::cout << " };\n";
}
void Console::log(std::vector<int> vect)
{
	std::cout << "|  vector<string> { ";

	for (std::vector<int>::iterator
		intP = vect.begin();
		intP != vect.end();
		intP++)
	{
		this->set_color(9);
		std::cout << "\"" << *intP << "\"";
		this->reset_color();
		std::cout << ", ";
	}
	std::cout << "\b\b";
	std::cout << " };\n";
}


void Console::set_color(int color)
{
	SetConsoleTextAttribute(this->handle, color);
}
void Console::reset_color()
{
	set_color();
}
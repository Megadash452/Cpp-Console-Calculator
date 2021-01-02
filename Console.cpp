#include "Console.h"

Console::Console()
{
	SetConsoleTextAttribute(this->handle, 7);
}

void Console::log(string msg, int color, bool new_line)
{
	this->set_color(color);

	std::cout << "|  ";
	for (string::iterator
		 charP = msg.begin();
		 charP != msg.end();
		 charP++)
	{
		if (*charP == '"')
			foo(charP, 2, true);
		else if (*charP == '\'' && *(charP + 2) == '\'')
			foo(charP, 3, true);
		else if (*charP == '<')
			foo(charP, 11, true);
		else if (*charP == ' ' && char_in_numbers(*(charP + 1)))
			foo(charP, 9, true);

		else if (*charP == 'c' && *(charP + 1) == '{')
		{
			string tempStr;
			for (string::iterator i = charP + 2; *i != '}'; i++)
			{
				tempStr.push_back(*i);
				if (*(i + 1) == '}')
					charP = i + 2;
			}
			this->foo(charP, stoi(tempStr));
		}

		std::cout << *charP;
	}
	if (new_line)
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

void Console::foo(string::iterator& charP, int color, bool keep_delims) // Before using, make sure that the string::iterator is in this->closeDelims map;
{
	string::iterator delimP = charP;

	if (closeDelims[*delimP])
	{
		if (!keep_delims)
			charP++;

		this->set_color(color);
		if (keep_delims)
		{
			for (; *charP != this->closeDelims[*delimP] ||
				charP == delimP;
				charP++)
				std::cout << *charP;
			std::cout << *charP;
		}
		else
			for (; *charP != this->closeDelims[*delimP];
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

#pragma once
#include <iostream>
#include <windows.h>

#include "Lib.h"

struct Console
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int default_color = 7;
	int text_color = this->default_color;
	int previous_color = 7;

	Console();

	void log(string msg);

	//void log(std::vector<const char*> vect);
	void log(std::vector<string> vect);
	void log(std::vector<char> vect);
	void log(std::vector<int> vect);

	void set_color(int color);
	void set_previous_color();
	void reset_color();
};


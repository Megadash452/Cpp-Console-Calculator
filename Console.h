#pragma once
#include <iostream>
#include <windows.h>

#include "Lib.h"

struct Console
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int previous_color = 7;

	Console();

	void log(const char* msg);
	void log(std::vector<string> vect);
	void log(std::vector<char> vect);
	void log(std::vector<int> vect);

	void set_color(int color = 7);
	void reset_color();
};


#pragma once
#include <iostream>
#include <stdexcept>
#include <windows.h>

#include "Lib.h"

struct Console
{
	// Rules:
	// "c{color}[part]" to apply color to a part of the string; (alternative: pass in the color as second parameter of console.log();

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int default_color = 7;
	int text_color = this->default_color;
	int previous_color = 7;

	static string Keywords[30];

	Console();

	void log(string msg, int color = 0, bool new_line = true);
	void input(string& var);
	//void input(int& var);

	void log_str(string str);
	void log_char(char c);
	void log_int(int i);

	//void log(std::vector<const char*> vect);
	void log(std::vector<string> vect);
	void log(std::vector<char> vect);
	void log(std::vector<int> vect);

	void set_color(int color);
	void set_previous_color();
	void reset_color();

private:
	void color_by_delim(string::iterator& charP, int color, bool keep_delims = false); // Before using, make sure that the string::iterator is in this->closeDelims map;
	void iterate_for_keywords(string::iterator& charP);
};


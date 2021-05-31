#pragma once
#include <iostream>
#include <windows.h>

#include "Calc Exceptions.h"
#include "Tree.h"

//#define println(x) std::cout <<"║  "<<x<<std::endl
//#define NEW_LINE "  ║\n║  "

#define PAUSE system("pause");

#define COLOR_DEFAULT 0

#define DARK_BLUE    1
#define DARK_GREEN   2
#define DARK_CYAN    3
#define DARK_RED     4
#define DARK_MAGENTA 5
#define DARK_YELLOW  6
#define GREY         7
#define DARK_GREY    8

#define BLUE         9
#define GREEN       10
#define CYAN        11
#define RED         12
#define MAGENTA     13
#define YELLOW      14
#define WHITE       15

#define HILIGT_DEFAULT(x)      x+0
#define HILIGT_DARK_BLUE(x)    x+16
#define HILIGT_DARK_GREEN(x)   x+32
#define HILIGT_DARK_CYAN(x)    x+48
#define HILIGT_DARK_RED(x)     x+64
#define HILIGT_DARK_MAGENTA(x) x+80
#define HILIGT_DARK_YELLOW(x)  x+96
#define HILIGT_GREY(x)         x+112
#define HILIGT_DARK_GREY(x)    x+128

#define HILIGT_BLUE(x)         x+144
#define HILIGT_GREEN(x)        x+160
#define HILIGT_CYAN(x)         x+176
#define HILIGT_RED(x)          x+192
#define HILIGT_MAGENTA(x)      x+208
#define HILIGT_YELLOW(x)       x+224
#define HILIGT_WHTIE(x)        x+240

#define SYS_PTR_DIGITS 16      // How many digits in a pointer for this system
                               // TODO: Make system dependable



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
	// template <typename Function> Console(Function);

	void log(string msg, int color=0, bool new_line=true);
	void log(string msg, bool new_line);
	//void log(lib::Tree);

	//void log(std::vector<const char*> vect);
	void log(std::vector<string>);
	void log(std::vector<char>);
	void log(std::vector<int>);

	//string input(string msg);
	void input(string& var);
	void input(int& var);

	void error(string error);
	void error(lib::calc_exception&);
	void warn(string warning);

	void log_node(lib::Node*, bool prnt_chldrn=true);
	void log_tree(const lib::Tree&);
	/// -- Inline Logs
	void log_ptr(const void*);
	void log_str(string);
	void log_char(char);
	void log_int(int);
	void log_dbl(double);


	void set_color(int color);
	void set_previous_color();
	void reset_color();

	std::vector<int> get_cursor_pos();
	void set_cursor_pos(int x, int y);
	void set_cursor_pos(std::vector<int> pos);

	void initializer_print();

	Console& operator <<(string);
	Console& operator <<(const char*);
	Console& operator <<(char);
	Console& operator <<(int);
	Console& operator <<(double);
	Console& operator <<(std::vector<string>);
	Console& operator <<(std::vector<char>);
	Console& operator <<(std::vector<int>);
	Console& operator <<(const void*);

	Console& operator <<(lib::Tree);
	Console& operator <<(lib::Node*);

private:
	void color_by_delim(const string&, string::iterator& charP, int color, bool keep_delims=false); // Before using, make sure that the string::iterator is in this->closeDelims map;
	void iterate_for_keywords(string::iterator& charP);
	
	void hprint(int printed=1);

	void new_line();
	void apply_padding();
	

	mutable int chars_printed;

	mutable int node_indent;

	int margin_size;
	int border_size;
	int padding_size;
	
	int text_area_width;
	int text_area_height;

	int width;
	mutable int height;
};

extern Console console;
//Console& console() {
//	static Console c;
//	return c;
//}
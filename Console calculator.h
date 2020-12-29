#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <variant>
#include <map>
using string = std::string;

bool char_in_string(char character, string str);

string::const_iterator find_closing(string::const_iterator it, string& str);
string::iterator find_closing(string::iterator it, string& str);

void vPrint(std::vector<string>& vect);
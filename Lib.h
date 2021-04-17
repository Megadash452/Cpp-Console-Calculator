#pragma once
#include <string>
#include <vector>
#include <array>
#include <variant>
#include <map>
using string = std::string;

#include "Console.h"
#include "Expression.h"

// Comparisons
#define char_in_operators(c) (c=='+'||c=='-'||c==(char)241||c=='*'||c=='/'||c=='^'||c=='!'||c=='%'||c=='|'||c=='('||c==')'||c=='.')
#define char_in_numbers(c) (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
#define char_in_constants(c) (c=='e'||c==(char)227||c==(char)237||c==(char)242||c==(char)243)
#define char_in_alphabet(c) (c=='a'||c=='b'||c=='c'||c=='d'||c=='f'||c=='g'||c=='h'||c=='i'||c=='j'||c=='k'||c=='l'||c=='m'||c=='n'||c=='o'||c=='p'||c=='q'||c=='r'||c=='s'||c=='t'||c=='u'||c=='v'||c=='w'||c=='x'||c=='y'||c=='z'||c==(char)159)
#define char_in_alphabetUpper(c) (c=='A'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F'||c=='G'||c=='H'||c=='I'||c=='J'||c=='K'||c=='L'||c=='M'||c=='N'||c=='O'||c=='P'||c=='Q'||c=='R'||c=='S'||c=='T'||c=='U'||c=='V'||c=='W'||c=='X'||c=='Y'||c=='Z')
#define char_in_symbols(c) (c==(char)228||c==(char)233||c==(char)244||c==(char)245||c==(char)248)
#define has_valid_expression_chars(c) (char_in_operators(c)||char_in_numbers(c)||char_in_constants(c)||char_in_alphabet(c)||char_in_alphabetUpper(c)||char_in_symbols(c))


namespace lib {
    extern std::map<char, char> closeDelims;
    extern std::map<char, char> openDelims;

    bool char_in_string(char character, string str);

    string lower_case(string str);
    string upper_case(string str);
    char lower_case(char c);
    char upper_case(char c);

    int integer(char c);
    int integer(string str, int base = 10);

    string to_string(int num);

    string::const_iterator find_closing(string::const_iterator it);
    string::iterator find_closing(string::iterator it);

    void split(string str, string delimeters, std::vector<string>& save_to, bool keep_delimeters = false);

    template<typename T>
    void vectorPrint(const std::vector<T>& vect)
    {
        std::cout << "std::vector: ";
        for (typename std::vector<T>::const_iterator
            elP = vect.begin();
            elP != vect.end();
            elP++)
        {
            std::cout << *elP;
            if (elP != vect.end() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }


    string get_command(string str, char split = ' ');
    std::vector<string> get_arguments(string str, int num_of_args, char split = ' ');
    //void organize(string from, string& command, std::vector<string>& arguments);

    //void end_command_turn(const string& comm, const std::vector<string>& args);
}
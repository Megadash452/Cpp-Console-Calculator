#pragma once
#include <string>
#include <vector>
#include <map>
using std::string;

// Comparisons
#define char_in_operators(c) (c=='+'||c=='-'||c==(char)241||c=='*'||c=='/'||c=='^'||c=='!'||c=='%'||c=='|'||c=='('||c==')'||c=='.')
#define char_in_numbers(c) (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
#define char_in_constants(c) (c=='e'||c==(char)227||c==(char)237||c==(char)242||c==(char)243)
#define char_in_alphabet(c) (c=='a'||c=='b'||c=='c'||c=='d'||c=='f'||c=='g'||c=='h'||c=='i'||c=='j'||c=='k'||c=='l'||c=='m'||c=='n'||c=='o'||c=='p'||c=='q'||c=='r'||c=='s'||c=='t'||c=='u'||c=='v'||c=='w'||c=='x'||c=='y'||c=='z'||c==(char)159)
#define char_in_alphabetUpper(c) (c=='A'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F'||c=='G'||c=='H'||c=='I'||c=='J'||c=='K'||c=='L'||c=='M'||c=='N'||c=='O'||c=='P'||c=='Q'||c=='R'||c=='S'||c=='T'||c=='U'||c=='V'||c=='W'||c=='X'||c=='Y'||c=='Z')
#define char_in_symbols(c) (c==(char)228||c==(char)233||c==(char)244||c==(char)245||c==(char)248)
#define char_in_punctuation(c) (c=='\''||c=='"'||c=='<'||c=='>'||c=='['||c==']'||c=='('||c==')'||c=='{'||c=='}'||c==' '||c=='.'||c==',')
#define has_valid_expression_chars(c) (char_in_operators(c)||char_in_numbers(c)||char_in_constants(c)||char_in_alphabet(c)||char_in_alphabetUpper(c)||char_in_symbols(c))

namespace lib {
    extern std::map<char, char> closeDelims;
    extern std::map<char, char> openDelims;

    bool char_in_string(char character, string str);

    string lower_case(string str);
    string upper_case(string str);
    char lower_case(char c);
    char upper_case(char c);

    int to_int(char c, int base=10);
    int to_int(string str, int base=10);
    double to_double(char c, int base=10);
    double to_double(string str, int base=10);
    int digits(int num, int base=10);

    string::const_iterator find_closing(string::const_iterator it);
    string::iterator find_closing(string::iterator it);

    void split(string str, string delimeters, std::vector<string>& save_to, bool keep_delimeters = false);


    string get_command(string str, char split = ' ');
    //std::vector<string> get_arguments(int argc, char** argv, int num_of_args);
}

//std::map<char, char> closeDelims()
//{
//    static std::map<char, char> closeDelims{ {
//        {'\'', '\''},
//        {'"', '"'},
//        {'<', '>'},
//        {'[', ']'},
//        {'(', ')'},
//        {'{', '}'},
//        {' ', ' '}
//    } };
//    return closeDelims;
//}
//std::map<char, char> openDelims()
//{
//    static std::map<char, char> openDelims{ {
//        {'\'', '\''},
//        {'"', '"'},
//        {'>', '<'},
//        {']', '['},
//        {')', '('},
//        {'}', '{'},
//        {' ', ' '}
//    } };
//    return openDelims;
//}
//
//static bool global_initialization = []()
//{
//    try {
//        closeDelims();
//        openDelims();
//        console();
//        return true;
//    }
//    catch (std::exception) {
//        return false;
//    }
//}();
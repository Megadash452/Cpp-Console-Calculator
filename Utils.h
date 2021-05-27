#pragma once
#include <string>
#include <vector>
#include <map>
using std::string;

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
    int digits(int num, int base = 10);

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
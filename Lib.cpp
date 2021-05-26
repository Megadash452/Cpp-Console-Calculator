#include "Lib.h"
#include "Calc Exceptions.h"

std::map<char, char> lib::closeDelims({
    {'\'', '\''},
    {'"', '"'},
    {'<', '>'},
    {'[', ']'},
    {'(', ')'},
    {'{', '}'},
    {' ', ' '}
});
std::map<char, char> lib::openDelims({
    {'\'', '\''},
    {'"', '"'},
    {'>', '<'},
    {']', '['},
    {')', '('},
    {'}', '{'},
    {' ', ' '}
});

bool lib::char_in_string(char character, string str)
{
    for (string::const_iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (character == *charP)
            return true;
    }
    return false;
}

/*template<typename Element>
bool lib::element_in_vector(Element el, std::vector<Element>& vect)
{

}*/

string lib::lower_case(string str)
{
    string returnStr;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (*charP > 64 && *charP < 91)
            returnStr.push_back(*charP + 32);
        else
            returnStr.push_back(*charP);
    }
    return returnStr;
}

string lib::upper_case(string str)
{
    string returnStr;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (*charP > 96 && *charP < 123)
            returnStr.push_back(*charP - 32);
        else
            returnStr.push_back(*charP);
    }
    return returnStr;
}

char lib::lower_case(char c)
{
    if (c > 64 && c < 91)
        return c + 32;
    else
        return c;
}

char lib::upper_case(char c)
{
    if (c > 96 && c < 123)
        return c - 32;
    else
        return c;
}

int lib::integer(char c) {
    return ((int)c) - 48;
}
int lib::integer(string str, int base)
{
    int num = 0;
    int place = 0;

    for (string::reverse_iterator
        charP = str.rbegin();
        charP != str.rend();
        charP++)
    {
        if (char_in_numbers(*charP) && base == 10)
        {
            num += integer(*charP) * (int)pow(base, place);
            place++;
        }
    }
    return num;
}

int lib::digits(int num, int base)
{
    if (!num)
        return 1;

    int i = 0;
    for (; num != 0; i++)
        num /= 10;
    return i;
}

string lib::to_string(int num)
{
    string returnStr;

    return string();
}


string::const_iterator lib::find_closing(string::const_iterator it)
{
    string::const_iterator opening = it;
    if (lib::closeDelims[*it])
    {
        int extraCount = 0;
        char target = lib::closeDelims[*it];
        for (; !(*it == '\0' || *it == '\n');)
        {
            it++;
            if (*it == target)
            {
                if (extraCount)
                    extraCount--;
                else
                    return it;
            }
            else if (*it == *opening)
                extraCount++;
        }
    }
    return opening;
}
string::iterator lib::find_closing(string::iterator it)
{
    string::iterator opening = it;
    if (lib::closeDelims[*it])
    {
        int extraCount = 0;
        char target = lib::closeDelims[*it];
        
        while (*it != '\0' && *it != '\n')
        {
            it++;
            try {
                if (*it == target)
                {
                    if (extraCount)
                        extraCount--;
                    else
                        return it;
                }
                else if (*it == *opening)
                    extraCount++;
            }
            catch (std::out_of_range e) {
                throw(std::out_of_range{e});
            }
        }
    }
    return opening;
}

void lib::split(string str, string delimeters, std::vector<string>& save_to, bool keep_delimeters)
{
    string::iterator left_over = str.begin();

    while (left_over != str.end())
        for (string::iterator
            charP = left_over;
            charP != str.end();
            charP++)
            if (lib::char_in_string(*charP, delimeters) || charP == str.end() - 1)
            {
                if (charP == str.end() - 1) {
                    string tempStr(left_over, charP + 1);
                    save_to.push_back(tempStr);
                }
                else {
                    string tempStr(left_over, charP);
                    save_to.push_back(tempStr);
                }

                if (keep_delimeters && charP != str.end() - 1) {
                    const char delimeter[] = { *charP, (char)0 };
                    save_to.push_back(delimeter);
                }
                left_over = charP + 1;
                break;
            }
}

string lib::get_command(string str, char split)
{
    string returnStr;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
        if (*charP == split)
            break;
        else
            returnStr.push_back(*charP);
    return returnStr;
}
std::vector<string> lib::get_arguments(int argc, char** argv, int num_of_args)
{
    std::vector<string> vect;
    for (int i = 2; i < argc; i++)
        vect.push_back(argv[i]);
    return std::vector<string>{};
}
std::vector<string> lib::get_arguments(string str, int num_of_args, char split)
{
    std::vector<string> vect;
    string::iterator left_over = str.begin();
    string push_backStr;
    bool in_quotes = false;

    while (left_over < str.end())
        for (string::iterator charP = left_over;
            charP != str.end(); charP++)
        {
            // determine the start of first argument
            if (*charP == split && left_over == str.begin() && !in_quotes)
            {
                left_over = charP + 1;
                break;
            }
            // when argument is enclosed in quotes
            else if (*charP == '"' && *(charP - 1) != '\\' && in_quotes)
            {
                vect.push_back(string{ left_over + 1, charP });
                if (charP <= str.end() - 2)
                    left_over = charP + 2;
                else
                    left_over = str.end();
                in_quotes = false;
                if (charP < str.end() - 1)
                    charP++;
            }
            // when reached the end of an argument on str
            else if ((*charP == split || charP == str.end()-1) && !in_quotes && *left_over != '"')
            {
                if (charP == str.end() - 1)
                    vect.push_back(string{ left_over, charP + 1 });
                else
                    vect.push_back(string{ left_over, charP });
                left_over = charP + 1;
                break;
            }

            // toggle the in_quote state
            if (*charP == '"' && *(charP - 1) != '\\')
                if (in_quotes)
                    in_quotes = false;
                else
                    in_quotes = true;
        }

    // if the num of args in the vector is GREATER than the desired num of args
    if ((unsigned int)vect.size() > (unsigned int)num_of_args)
        console.warn(
            "Too many arguments. Please provide " + std::to_string(num_of_args) + " arguments\n" +
            "              Unnecessary arguments were ignored"
        );
    // if the num of args in the vector is LESS than the desired num of args
    else if ((unsigned int)vect.size() < (unsigned int)num_of_args)
        throw lib::argument_error{ "Too few arguments. Please provide " + std::to_string(num_of_args) + " arguments" };

    // only return the disired num of args
    return std::vector<string>{ vect.begin(), vect.begin() + num_of_args };
}
//void lib::organize(string source, string& command, std::vector<string>& arguments)
//{
//    command = lib::get_command(source);
//    if (command == "calculate" || command == "calc")
//        arguments = lib::get_arguments(source, 1);
//    else if (command == "add"      || command == "sum"  ||
//             command == "subtract" || command == "subt" ||
//             command == "multiply" || command == "mult" ||
//             command == "divide"   || command == "div"  ||
//             command == "store")
//                 arguments = lib::get_arguments(source, 2);
//    else if (command == "stop" || command == "quit" || command == "exit" ||
//             command == "variables" || command == "vars" ||
//             command == "help"      || command == "h")
//        arguments = lib::get_arguments(source, 0);
//}

/*void lib::end_command_turn(const string& comm, const std::vector<string>& args)
{
    std::cout << "___";
    for (string::const_iterator
        charP = comm.begin();
        charP != comm.end();
        charP++)
        std::cout << '_';

    for (std::vector<string>::const_iterator
        argP = args.begin();
        argP != args.end();
        argP++)
    {
        for (string::const_iterator
            strP = (*argP).begin();
            strP != (*argP).end();
            strP++)
            std::cout << '_';
        std::cout << '_';
    }
    std::cout << "\n\n";
        
}*/


/// --- EXCEPTIONS ---

//lib::calc_exception::calc_exception() {
//}
//
//lib::calc_exception::calc_exception(string str)
//    : std::exception(str.c_str())
//{
//    
//}
//
//lib::syntax_error::syntax_error() {
//}
//
//lib::syntax_error::syntax_error(string w)
//    : calc_exception(w)
//{
//
//}
//
//const string lib::calc_exception::_type{ "Calc Expression" };
//const string lib::syntax_error::_type{ "Syntax Error" };
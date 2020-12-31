#include "Lib.h"

bool char_in_string(char character, string str)
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

template<typename Element>
bool element_in_vector(Element el, std::vector<Element>& vect)
{

}

string lower_case(string str)
{
    string returnStr;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (*charP >= 65 && *charP <= 90)
            returnStr.push_back(*charP + 32);
        else
            returnStr.push_back(*charP);
    }
    return returnStr;
}

int integer(char c) {
    return ((int)c) - 48;
}
int integer(string str, int base)
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
            num += integer(*charP) * pow(base, place);
            place++;
        }
    }
    return num;
}

string to_string(int num)
{
    string returnStr;

    return string();
}


string::const_iterator find_closing(string::const_iterator it, string& str)
{
    if (*it == '(')
    {
        int parenthesisCount = 0;
        for (string::const_iterator i = it; i != str.end(); i++)
        {
            if (*i == '(' && i != it)
                parenthesisCount++;
            if (*i == ')')
            {
                if (parenthesisCount)
                    parenthesisCount--;
                else
                    return i;
            }
        }
    }
}
string::iterator find_closing(string::iterator it, string& str)
{
    if (*it == '(')
    {
        int parenthesisCount = 0;
        for (string::iterator i = it; i != str.end(); i++)
        {
            if (*i == '(' && i != it)
                parenthesisCount++;
            if (*i == ')')
            {
                if (parenthesisCount)
                    parenthesisCount--;
                else
                    return i;
            }
        }
    }
    return it;
}

void split(string str, string delimeters, std::vector<string>& save_to, bool keep_delimeters = false)
{
    std::vector<char> delims;

    for (string::iterator
        charP = delimeters.begin();
        charP != delimeters.end();
        charP++)
            delims.push_back(*charP);

    // splitting
}

void vPrint(std::vector<string>& vect)
{
    std::cout << "std::vector: ";
    for (std::vector<string>::const_iterator
        strP = vect.begin();
        strP != vect.end();
        strP++)
    {
        std::cout << *strP << ", ";
    }
    std::cout << std::endl;
}


string get_command(string str, char split)
{
    string returnStr;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
    {
        if (*charP == split)
            break;
        else
            returnStr.push_back(*charP);
    }
    return returnStr;
}
std::vector<string> get_arguments(string str, int num_of_args, char split)//TODO: throw error when missing arguments
{
    std::vector<string> returnVect;
    string::iterator left_over = str.begin();
    string push_backStr;

    for (int i = 0; i < num_of_args + 1; i++)
    {
        for (string::iterator
            charP = left_over;
            charP != str.end();
            charP++)
        {
            if (*charP == split && left_over == str.begin())
            {
                left_over = charP + 1;
                break;
            }
            else if (*charP == split || charP == str.end()-1)
            {
                if (charP == str.end() - 1) {
                    string tempStr(left_over, charP + 1);
                    returnVect.push_back(tempStr);
                }
                else {
                    string tempStr(left_over, charP);
                    returnVect.push_back(tempStr);
                }
                left_over = charP + 1;
                break;
            }
        }
    }
    return returnVect;
}

void organize(string from, string& command, std::vector<string>& arguments)
{
    command = get_command(from);
    if (command == "calculate" || command == "calc")
        arguments = get_arguments(from, 1);
    if (command == "add" || command == "sum" ||
        command == "subtract" || command == "subt" ||
        command == "multiply" || command == "mult" ||
        command == "divide" || command == "div")
        arguments = get_arguments(from, 2);
}
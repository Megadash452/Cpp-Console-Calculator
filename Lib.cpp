#include "Lib.h"

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

template<typename Element>
bool element_in_vector(Element el, std::vector<Element>& vect)
{

}

string lib::lower_case(string str)
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
            num += integer(*charP) * pow(base, place);
            place++;
        }
    }
    return num;
}

string lib::to_string(int num)
{
    string returnStr;

    return string();
}


string::const_iterator lib::find_closing(string::const_iterator it, string& str)
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
string::iterator lib::find_closing(string::iterator it, string& str)
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
std::vector<string> lib::get_arguments(string str, int num_of_args, char split)//TODO: throw error when missing arguments
{
    std::vector<string> returnVect;
    string::iterator left_over = str.begin();
    string push_backStr;

    for (int i = 0; i < num_of_args + 1; i++)
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
    
    int actual_num_of_args = 0;
    for (string::iterator
        charP = str.begin();
        charP != str.end();
        charP++)
        if (*charP == split)
            actual_num_of_args++;

    if (actual_num_of_args > num_of_args)
        std::cout << "|  --WARNING!--  Too many arguments. Please provide " << num_of_args << " arguments\n"
                     "|                Unnecessary arguments were ignored\n";
    else if (actual_num_of_args < num_of_args)
        std::cout << "|  --WARNING!--  Too few arguments. Please provide " << num_of_args << " arguments\n";

    return returnVect;
}
void lib::organize(string from, string& command, std::vector<string>& arguments)
{
    command = lib::get_command(from);
    if (command == "calculate" || command == "calc")
        arguments = lib::get_arguments(from, 1);
    else if (command == "add" || command == "sum" ||
        command == "subtract" || command == "subt" ||
        command == "multiply" || command == "mult" ||
        command == "divide" || command == "div")
        arguments = lib::get_arguments(from, 2);
}

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
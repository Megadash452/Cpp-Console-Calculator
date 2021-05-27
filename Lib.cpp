#include "Lib.h"
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
        else if ((*charP == split || charP == str.end() - 1) && !in_quotes && *left_over != '"')
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
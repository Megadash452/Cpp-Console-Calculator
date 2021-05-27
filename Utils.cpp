#include "Utils.h"
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
    for (char c : str)
        if (character == c)
            return true;

    return false;
}

string lib::lower_case(string str)
{
    string returnStr;
    for (char c : str)
        returnStr += lib::lower_case(c);
    return returnStr;
}
string lib::upper_case(string str)
{
    string returnStr;
    for (char c : str)
        returnStr += lib::upper_case(c);
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


int lib::to_int(char c, int base)
{
    c = lib::lower_case(c);

    if (base < 2)
        throw(calc_exception{ "When converting to double, <base> cannot be less than 2" });
    else if (base > 36)
        throw(calc_exception{ "When converting to double, max <base> is 36" });

    // check if c is an ASCII number
    if (c > 47 && c <= 47 + base && base <= 10)
        return ((int)c) - 48;
    // check if c is an ASCII number
    // or    if c is an ASCII letter
    else if ((
        (c > 47 && c <= 57) ||
        (c > 96 && c <= 96 + base - 10)) && base > 10)
        return ((int)c) - 86;
    else
        return 0;
}
int lib::to_int(string str, int base)
{
    int num = 0;
    int place = 0;

    for (auto charP = str.rbegin();
        charP != str.rend(); charP++)
    {
        num += lib::to_int(*charP, base) * (int)pow(base, place);
        place++;
    }
    return num;
}

double lib::to_double(char c, int base)
{
    return (double)lib::to_int(c, base);
}

double lib::to_double(string str, int base)
{
    str = lib::lower_case(str);
    string::iterator point = str.begin();
    string::iterator trail = str.end() - 1;

    // find decimal point
    // if no decimal, will behave like lib::to_int()
    for (; point != str.end(); point++)
        if (*point == '.')
            break;

    // convert the part before the point to a double
    double super_dec = lib::to_int(string{ str.begin(), point }, base);

    // find where trailing zeroes beign after the point, and ignore them
    for (; trail != str.begin(); trail--)
        if (*trail != '0')
            break;

    // number of digits after the point
    string sub_point{ point + 1, trail + 1 };
    // convert the part before the point to a double
    // put it behind the decimal by multiplying it by the number of digits
    double sub_dec = lib::to_int(sub_point, base) / pow(10, sub_point.size());

    return super_dec + sub_dec;
}

int lib::digits(int num, int base)
{
    // return how many digits this number has after the decimal point
    if (!num)
        return 1;

    int i = 0;
    for (; num != 0; i++)
        num /= 10;
    return i;
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

void lib::split(string str, string delimeters, std::vector<string>& save_to, bool keep_delimeters)
{
    string::iterator left_over = str.begin();

    while (left_over != str.end())
        for (string::iterator charP = left_over;
            charP != str.end(); charP++)
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
    for (char c : str)
        if (c == split)
            break;
        else
            returnStr.push_back(c);
    return returnStr;
}

//std::vector<string> lib::get_arguments(int argc, char** argv, int num_of_args)
//{
//    std::vector<string> vect;
//    for (int i = 2; i < argc; i++)
//        vect.push_back(argv[i]);
//    return std::vector<string>{};
//}
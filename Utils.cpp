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
    else if (base > 10)
        if (c > 47 && c <= 57)
            ;
        else if (c > 96 && c <= 96 + base - 10)
            return ((int)c) - 86;
        else;
    else
        throw std::exception{ (
            string{ "cannot convert " } + c + " in base "
          + std::to_string(base) + ". Try another base"
        ).c_str()};
}
int lib::to_int(string str, int base)
{
    int num = 0;
    int place = 0;

    for (auto charP = str.rbegin();
        charP != str.rend(); charP++)
    {
        int result = 0;
        try {
            int result = lib::to_int(*charP) * (int)pow(base, place);
            if ((result > 0 && *charP > 48) ||
                (result == 0 && *charP == 48))
                num += result;
            place++;
        }
        catch (std::exception) {
        }
    }
    if (str[0] == '-')
        return -num;
    return num;
}

double lib::to_double(char c, int base)
{
    return (double)lib::to_int(c, base);
}

double lib::to_double(string str, int base)
{
    str = lib::lower_case(str);
    

    // check base
    if (str[0] == '+' || str[0] == '-')
        if (str[1] == '0')
            if (str[2] == 'x') {
                base = 16;
                str.erase(str.begin() + 1, str.begin() + 3);
            }
            else if (str[2] == 'b') {
                base = 2;
                str.erase(str.begin() + 1, str.begin() + 3);
            }
            else;
        else;
    else
        if (str[0] == '0')
            if (str[1] == 'x') {
                base = 16;
                str.erase(str.begin(), str.begin() + 2);
            }
            else if (str[1] == 'b') {
                base = 2;
                str.erase(str.begin(), str.begin() + 2);
            }

    // find decimal point
    // if no decimal, will behave like lib::to_int()
    string::iterator point = str.begin();
    string::iterator trail = str.end() - 1;
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
    string sub_point = "";
    if (point < str.end())
        sub_point = string{ point + 1, trail + 1 };
    // convert the part before the point to a double
    // put it behind the decimal by multiplying it by the number of digits
    double sub_dec = lib::to_int(sub_point, base) / pow(10, sub_point.size());

    return super_dec + sub_dec;
}

int lib::digits(int num, int base)
{
    // return how many digits this number has (e.g. 23 -> 2)
    // TODO: take base into account
    if (!num)
        return 1;

    int i = 0;
    for (; num != 0; i++)
        num /= 10;
    return i;
}

int lib::integer_digits(double num, int base)
{
    // return how many digits this number has before the decimal (e.g. [73].581 -> 2)
    // TODO: take base into account
    if (!num)
        return 1;

    int i = 0;
    for (; num > 1; i++)
        num /= 10;
    return i;
}

int lib::fractional_digits(double num, int base)
{
    // return how many digits this number has after the decimal (e.g. 73.[581] -> 3)
    // TODO: take base into account
    if (!num)
        return 1;

    std::ostringstream buf;
    buf << std::fixed
        << std::setprecision(11);
    buf << num;

    int i = 0;
    bool counting = false;
    string str = buf.str();
    for (string::reverse_iterator it = str.rbegin(); it != str.rend(); it++)
    {
        if (*it == '.' || i >= 11)
            break;

        else if (*it != '0' && !counting)
            counting = true;

        if (counting)
            i++;
    }
    return i;
}


string::const_iterator lib::find_closing(string::const_iterator it, const string& str)
{
    string::const_iterator opening = it;
    if (lib::closeDelims[*it])
    {
        int extraCount = 0;
        char target = lib::closeDelims[*it];
        while (*it != '\n' && it < str.end())
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
string::iterator lib::find_closing(string::iterator it, const string& str)
{
    // may cause errors if closer doesnt exist
    string::iterator opening = it;
    if (lib::closeDelims[*it])
    {
        int extraCount = 0;
        char target = lib::closeDelims[*it];

        while (*it != '\n' && it < str.end())
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

string::iterator lib::find_opening(string::iterator it, const string& str)
{
    // may cause errors if closer doesnt exist
    string::iterator closing = it;
    if (lib::openDelims[*it])
    {
        int extracount = 0;
        char target = lib::openDelims[*it];

        while (*it != '\n' && it > str.begin())
        {
            it--;
            if (*it == target)
            {
                if (extracount)
                    extracount--;
                else
                    return it;
            }
            else if (*it == *closing)
                extracount++;
        }
    }
    return closing;
}

string::reverse_iterator lib::find_closing(string::reverse_iterator it, const string& str)
{
    // may cause errors if closer doesnt exist
    // TODO: broken, fix
    string::reverse_iterator opening = it;
    if (lib::closeDelims[*it])
    {
        int extraCount = 0;
        char target = lib::closeDelims[*it];

        while (*it != '\n' && it > str.rbegin())
        {
            it--;
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

string::reverse_iterator lib::find_opening(string::reverse_iterator it, const string& str)
{
    // may cause errors if closer doesnt exist
    string::reverse_iterator closing = it;
    if (lib::openDelims[*it])
    {
        int extracount = 0;
        char target = lib::openDelims[*it];

        while (*it != '\n' && it < str.rend())
        {
            it++;
            if (*it == target)
            {
                if (extracount)
                    extracount--;
                else
                    return it;
            }
            else if (*it == *closing)
                extracount++;
        }
    }
    return closing;
}

void lib::split(string str, string delimeters, std::vector<string>& save_to, bool keep_delimeters)
{
    string::iterator left_over = str.begin();

    while (left_over != str.end())
        for (string::iterator charP = left_over;
            charP != str.end(); charP++)
            if (lib::char_in_arr(*charP, delimeters) || charP == str.end() - 1)
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
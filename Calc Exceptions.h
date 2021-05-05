#pragma once
#include <exception>
#include <string>
using std::string;

namespace lib {
    struct calc_exception : public std::exception
    {
        calc_exception();
        calc_exception(string str);

        static string type() { return "Calc Exception"; }
        // virtual string type() { return "Calc Exception"; }
    };

    struct syntax_error : public calc_exception
    {
        syntax_error();
        syntax_error(string str);

        static string type() { return "Syntax Error"; }
        // string type() override { return "Calc Exception"; }
    };
}
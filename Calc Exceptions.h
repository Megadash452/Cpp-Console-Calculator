#pragma once
#include <exception>
#include <string>
using std::string;

namespace lib {
    struct calc_exception : public std::exception
    {
        calc_exception()
            : _type("Calc Exception") {}

        calc_exception(string what) 
            : _type("Calc Exception"), std::exception(what.c_str()) {}

        //string type() { return this->_type; }
        virtual string type() { return "Calc Exception"; }
    private:
        string _type;
    };

    struct syntax_error : public calc_exception
    {
        syntax_error()
            : _type("Syntax Error") {}

        syntax_error(string what) // string where_, string::iterator p
            : _type("Syntax Error"), calc_exception(what.c_str())
        {
            //this->_where = string{p - max_offset, p + max_offset};
        }

        //string type() { return this->_type; }
        string where() { return this->_where; };
        string type() override { return "Syntax Error"; }
    private:
        static const uint8_t max_offset = 3;
        string _type;
        string _where; // const
    };
}
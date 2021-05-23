#pragma once
#include <exception>
#include <string>
using std::string;

namespace lib {
    struct calc_exception : public std::exception
    {
        calc_exception(string what="") 
            : _type("Calc Exception"), std::exception(what.c_str()) {}

        virtual string type() { return this->_type; }
    private:
        string _type;
    };


    struct syntax_error : public calc_exception
    {
        syntax_error(string what="") // string where_, string::iterator p
            : _type("Syntax Error"), calc_exception(what.c_str())
        {
            this->_where = ""; //string{p - max_offset, p + max_offset};
        }

        string where() { return this->_where; };
        string type() override { return this->_type; }
    private:
        static const uint8_t max_offset = 3;
        string _type;
        string _where; // const
    };


    struct argument_error : public calc_exception
    {
        argument_error(string what="")
            : _type("Argument Error"), calc_exception(what.c_str()) {}

        string type() override { return this->_type; }
    private:
        string _type;
    };


    struct store_error : public calc_exception
    {
        store_error(string what="")
            : _type("Storing Error"), calc_exception(what.c_str()) {}

        string type() override { return this->_type; }
    private:
        string _type;
    };
}
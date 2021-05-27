#pragma once
#include <array>
#include <assert.h>

// Forward Declaration


#include "Utils.h"
#include "Calc Exceptions.h"
#include "Tree.h"
#include "Console.h"

#include "Expression.h"


namespace lib {
    std::vector<string> get_arguments(string str, int num_of_args, char split = ' ');
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
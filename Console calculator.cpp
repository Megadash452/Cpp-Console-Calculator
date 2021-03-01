#include "Lib.h"

//#define print(x) std::cout << x << std::endl

/*#if _DEBUG
#define announce(x) std::cout<<x<<std::endl
#define announce_inExpression(type, exp, x) std::cout<<type<<" ("<<exp[x]<<") in exp["<<x<<']'<<std::endl
#else
#define announce_inExpression(type, exp, x)
#endif*/


class Function
{
private:
public:
    static int evaluateExpression(Expression expression)
    {

    }
};

bool var_defined(const string& var, std::map<string, Expression>& vars)
{
    if (vars.find(var) == vars.end())
        return false;
    else
        return true;
}

int main()
{
    //if (argc - 1)
        //std::cout << argc << " arguments passed from outside; omitted\n";

    Console console;

    string user_input;
    string command;
    std::vector<string> arguments;
    std::map<string, Expression> variables;

    std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    console.log("");
    console.log("What do you want to do? (type \"help\" or \"h\" to see your options)");

    while (true)
    {
        std::cout << "|  --> ";

        console.input(user_input);

        try {
            lib::organize(user_input, command, arguments);
        } catch (string error) { // TODO:bad: use std::exception instead
            console.error(error);
            continue;
        }
        command = lib::lower_case(command);


        // TODO: may be Inefficient; use map with function pointers
        if (command == "help" || command == "h")
        {
            std::cout << "|\n";
             console.log("c{6}[Commands:]");
             console.log("  c{12}[stop], c{12}[quit], c{12}[exit] (args: c{8}[None]):");
             console.log("    c{6}[--] Exit out of the program.");
             console.log("");
             console.log("  c{14}[calculate], c{14}[calc] (args: c{10}[Expression]<string>):");
             console.log("    c{6}[--] Use the calculator.");
             console.log("");
             console.log("  c{11}[store] (args: c{10}[Expression]<string>):");
             console.log("    c{6}[--] Store a variable to use later. You can always redefine a variable.");
             console.log("");
             console.log("  c{13}[variables], c{13}[vars] (args: c{8}[None]):");
             console.log("    c{6}[--] See all stored variables.");
             console.log("");
        }
        else if (command == "stop" || command == "quit" || command == "exit") {
            std::cout << "|  goodbye!";
            exit(0);
        }
        else if (command == "add" || command == "sum")
        {

        }
        else if (command == "subtract" || command == "subt")
        {

        }
        else if (command == "multiply" || command == "mult")
        {

        }
        else if (command == "divide" || command == "div")
        {
            
        }
        else if (command == "calculate" || command == "calc")
        {
            try {
                Expression e(arguments[0]);
                e.simplify();
                console.log("result: c{9}[" + e.expression + "]", false);
            }
            catch (string error) { // TODO:bad: use std::exception instead
                console.error("Error calculating expression because: " + error);
            }
        }
        else if (command == "store")
        {
            try {
                Expression e(arguments[1]);
                e.simplify();

                if (char_in_constants(arguments[0][0]))
                    console.error("first letter of variable{ c{11}[" + arguments[0] + "] } cannot be a predefined constant.");
                else if (char_in_numbers(arguments[0][0]) || char_in_operators(arguments[0][0]) || char_in_symbols(arguments[0][0]))
                    console.error("first letter of variable{ c{11}[" + arguments[0] + "] } cannot be a number or symbol.");
                else if (char_in_alphabet(arguments[0][0]) || char_in_alphabetUpper(arguments[0][0]))
                {
                    if (var_defined(arguments[0], variables))
                        variables[arguments[0]] = e;
                    else
                        variables.insert(std::pair<string, Expression>(arguments[0], e));
                    console.log("c{11}[" + arguments[0] + "] = c{9}[" + variables[arguments[0]].expression + ']');
                }
            }
            catch (string error) { // TODO:bad: use std::exception instead
                console.error("Could not store variable because: " + error);
            }
        }
        else if (command == "variables" || command == "vars")
        {
            for (const auto& [var, exp] : variables)
            {
                console.log("c{11}[" + var + "] = c{9}[" + exp.expression + ']');
            }
        }
        else
        {
            console.error("\"" + command + "\" is not a valid command.");
        }
        console.log("");
        // std::cout << "__________________________________________________________________________\n\n\n";
    }
}
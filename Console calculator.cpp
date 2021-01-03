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


int main()
{
    //if (argc - 1)
        //std::cout << argc << " arguments passed from outside; omitted\n";

    Console console;
    int sample;

    string user_input;
    string command;
    std::vector<string> arguments;

    while (true)
    {
        console.log("What do you want to do? (type \"help\" or \"h\" if you don't know what you can do)");
        std::cout << "|  --> ";

        console.input(user_input);

        lib::organize(user_input, command, arguments);
        command = lib::lower_case(command);

        //console.log({1, 2});


        // TODO: Inefficient; use map with function pointers
        if (command == "help" || command == "h")
        {
            std::cout << "|\n";
             console.log("c{6}[Commands:]");
             console.log("  c{12}[stop], c{12}[quit], c{12}[exit] (args: Null):");
             console.log("    c{6}[--] Exit out of the program.");
             console.log("");
             console.log("  c{14}[calculate], c{14}[calc] (args: c{10}[Expression]<string>):");
             console.log("    c{6}[--] Use the calculator.");
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
            Expression e(arguments[0]);
            console.log("result: ", 0, false);
            e.print();
        }
        else
        {
            console.log("c{4}[--Error--] \"" + command + "\" is not a valid command.");
        }
        std::cout << "__________________________________________________________________________\n\n\n";
    }


    std::cout << "\n-END-";
    getline(std::cin, user_input);
}
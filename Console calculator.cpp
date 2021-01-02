#include "Lib.h"
#include "Expression.h"

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

    string user_input;
    string command;
    std::vector<string> arguments;

    while (true)
    {
        console.log("What do you want to do? (type \"help\" or \"h\" if you don't know what you can do)");
        std::cout << "|  --> ";

        console.set_color(8);
        getline(std::cin, user_input);
        console.reset_color();

        lib::organize(user_input, command, arguments);
        command = lib::lower_case(command);

        //console.log({1, 2});


        // TODO: Inefficient; use map with function pointers
        if (command == "help" || command == "h")
        {
            std::cout << "|\n";
             console.log("Commands:");
             console.log("  stop, quit, exit (args: Null):");
             console.log("    -- Exit out of the program.");
             console.log("\n");
             console.log("  calculate, calc (args: Expression<string>):");
             console.log("  -Note: No support for decimals, yet.-");
             console.log("    -- Use the calculator.");
             console.log("\n");
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
            std::cout << "|  result: ";
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
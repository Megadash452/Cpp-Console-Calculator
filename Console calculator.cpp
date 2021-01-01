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
    Console console;

    string user_input;
    string command;
    std::vector<string> arguments;

    //if (argc - 1)
    {
        //std::cout << argc << " arguments passed from outside; omitted\n";
    }

    //for (int i = 0; i < 255; i++)
    //{
        //SetConsoleTextAttribute(console.handle, i);
        console.log(Expression::operators);
        console.log(Expression::numbers);
        console.log(std::vector<int>{1, 2, 3});
    //}

    while (false)
    {
        std::cout << "|  What do you want to do? (type \"help\" if you don't know what you can do)" << std::endl <<
                     "|  --> ";

        console.set_color(8);
        getline(std::cin, user_input);
        console.reset_color();

        lib::organize(user_input, command, arguments);
        command = lib::lower_case(command);

        //console.log({1, 2});


        // TODO: Inefficient; use map with function pointers
        if (command == "help" || command == "h")
        {
            std::cout << "|\n|  Commands:"                                     << std::endl <<
                         "|    stop, quit, exit (args: Null):"                 << std::endl <<
                         "|      -- Exit out of the program."                  << std::endl <<
                         "|"                                                   << std::endl <<
                         "|    calculate, calc (args: Expression<string>):"    << std::endl <<
                         "|    -Note: No support for decimals, yet.-"          << std::endl <<
                         "|      -- Use the calculator."                       << std::endl <<
                         "|\n";
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
            std::cout << "|  --Error-- \"" << command << "\" is not a valid command\n";
        }
        std::cout << "__________________________________________________________________________\n\n\n";
    }


    std::cout << "\n-END-";
    getline(std::cin, user_input);
}
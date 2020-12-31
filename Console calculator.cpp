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
    string user_input;
    string command;
    std::vector<string> arguments;

    while (true)
    {
        std::cout << "What do you want to do?\nOptions:\n  this\n>";
        getline(std::cin, user_input);

        lib::organize(user_input, command, arguments);
        command = lib::lower_case(command);

        // TODO: Inefficient; use map with function pointers
        if (command == "stop" || command == "quit" || command == "exit") {
            std::cout << "goodbye!";
            exit(0);
        }
        else if (command == "add" || command == "sum")
        {
            lib::end_command_turn(command, arguments);
        }
        else if (command == "subtract" || command == "subt")
        {
            lib::end_command_turn(command, arguments);
        }
        else if (command == "multiply" || command == "mult")
        {
            lib::end_command_turn(command, arguments);
        }
        else if (command == "divide" || command == "div")
        {
            lib::end_command_turn(command, arguments);
        }
        else if (command == "calculate" || command == "calc")
        {
            Expression e(arguments[0]);
            e.print();
            lib::end_command_turn(command, arguments);
        }
        else
        {
            std::cout << "\"" << command << "\" - invalid command\n-";
            for (string::iterator
                strP = command.begin();
                strP != command.end();
                strP++)
                std::cout << "-";
            std::cout << "-------------------\n\n";
        }
    }


    std::cout << "\n-END-";
    getline(std::cin, user_input);
}
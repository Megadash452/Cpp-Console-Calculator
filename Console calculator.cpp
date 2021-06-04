#include "Lib.h"


//class Function
//{
//private:
//public:
//    static int evaluateExpression(Expression expression)
//    {
//
//    }
//};


int main(int argc, const char** argv)
{
    // print commands from argv
#if _DEBUG
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++)
        std::cout << argv[i] << ", ";
    std::cout << '\n';
#endif

    // set up console borders and such
    console.initializer_print();

    string user_input;
    string command;
    std::vector<string> arguments;


    std::map<string, int> h;
    h.insert(std::pair<string, int>{string{ "" }, 2});

    /*std::map<string, Expression*> variables{
        {"ans", new Expression}
    };*/
    

    for (int iteration=0; true; iteration++)
    {
        if (argc < 2 || iteration > 0)
            console.input(user_input);
        else
        {
            for (int i = 1; i < argc; i++) {
                if (i < 2)
                    user_input += argv[i];
                else
                    user_input += '"' + string{ argv[i] } + '"';
                if (i != argc-1)
                    user_input += ' ';
            }
            console.log("--> c{8}[" + user_input + "]");
        }
            
        command = lib::get_command(lib::lower_case(user_input));

        try {
            if (command == "help" || command == "h")
            {
                console.log(string{ "\nc{6}[Commands:]\n" }
                       +    "  c{12}[stop], c{12}[quit], c{12}[exit] (args: c{8}[None]):\n"
                       +    "    c{6}[--] Exit out of the program.\n\n"

                       +    "  c{14}[calculate], c{14}[calc] (args: c{10}[Expression]<string>):\n"
                       +    "    c{6}[--] Use the calculator.\n"
                       +    "    c{6}[--] You can also type in anything that isn't a command.\n\n"

                       +    "  c{11}[store], c{11}[var] (args: c{10}[Expression]<string>):\n"
                       +    "    c{6}[--] Store a variable to use later. Variables can be redifined.\n\n"

                       +    "  c{13}[variables], c{13}[vars] (args: c{8}[None]):\n"
                       +    "    c{6}[--] See all stored variables.\n\n\n"


                       +    "c{6}[Correct Syntax:]\n"
                       +    "  c{3}[Numbers]:\n"
                       +    "    c{2}[-type-] Numbers can be integers (e.g. c{12}[24]) or floating point\n"
                       +    "           (e.g. 24c{12}[.]56).\n\n"

                       +    "    c{2}[-base-] base 10 numbers (e.g. 432) have digits\n"
                       +    "           0-9 (10 digits, hence base 10) Numbers can also be of base\n"
                       +    "           16 (e.g. c{12}[0x]6a7f) a.k.a Hexadecimal or base 2 (e.g. c{12}[0b]1011)\n"
                       +    "           a.k.a binary.\n\n"

                       +    "  c{3}[Expression]:\n"
                       +    "    c{2}[-Structure-] Expressions are series of one or more mathematical\n"
                       +    "                operations (e.g. 2+2).\n\n"

                       +    "  c{3}[Variables]:\n"
                       +    "    c{2}[-naming-]    Variable names are 1-lettered and may hold an expression.\n"
                       +    "                Variables can be named with multiple letters if they are\n"
                       +    "                given a subscript. Name cannot be a number.\n\n"

                       +    "    c{2}[-subscript-] To give a variable a superscript (i.e. a second name after\n"
                       +    "                its letter) add an underscore (c{9}[_]) (e.g. hc{12}[_]var2). Subscript\n"
                       +    "                may also include numbers.\n\n"
                );
            }
            else if (command == "stop" || command == "quit" || command == "exit") {
                console.log("goodbye!");
                #if _DEBUG
                    PAUSE
                #endif
                exit(0);
            }
            else if (command == "add" || command == "sum")
            { arguments = lib::get_arguments(user_input, 2);

            }
            else if (command == "subtract" || command == "subt")
            { arguments = lib::get_arguments(user_input, 2);

            }
            else if (command == "multiply" || command == "mult")
            { arguments = lib::get_arguments(user_input, 2);

            }
            else if (command == "divide" || command == "div")
            { arguments = lib::get_arguments(user_input, 2);
            
            }

            else if (command == "calculate" || command == "calc")
            { arguments = lib::get_arguments(user_input, 1);
                Expression* e = new Expression{ arguments[0] };
                e->simplify();

                Expression::set_var("ans", e);
                console.log("\nresult: c{9}[" + e->expression + "]");
            }

            else if (command == "store" || command == "var")
            { arguments = lib::get_arguments(user_input, 2);
                Expression::set_var(arguments[0], arguments[1]);
            }

            else if (command == "variables" || command == "vars")
            {
                for (std::pair<string, Expression*> pair : Expression::get_vars())
                {
                    if (pair.second != nullptr)
                    {
                        if (pair.second->expression != "")
                            console.log("c{11}[" + pair.first + "] = c{9}[" + pair.second->expression + "]");
                        else
                            console.log("c{11}[" + pair.first + "] = c{1}[Null]");
                        delete pair.second;
                    }
                    else
                        console.log("c{11}[" + pair.first + "] = c{1}[Null]");
                }
            }
            else if (command == "amogus") {
                console.log("When the Imposter is c{12}[sus!] c{14}[:flushed:]");
            }
            else {
                // defaults to calculate command, but every argument is part of the expression
                arguments = lib::get_arguments(user_input);
                for (string arg : arguments)
                    command += arg;

                Expression* e = new Expression{ command };
                e->simplify();

                Expression::set_var("ans", e);
                console.log("\nresult: c{9}[" + e->expression + "]");
            }
        }
        catch (lib::argument_error e) {
            console.error(e);
        }
        catch (lib::syntax_error e) {
            console.error(e);
        }
        catch (lib::store_error e) {
            console.error(e);
        }
        catch (lib::var_error e) {
            console.error(e);
        }
        console.log("");
    }

    PAUSE
}
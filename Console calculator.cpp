#include "Lib.h"

//#define print(x) std::cout << x << std::endl

/*#if _DEBUG
#define announce(x) std::cout<<x<<std::endl
#define announce_inExpression(type, exp, x) std::cout<<type<<" ("<<exp[x]<<") in exp["<<x<<']'<<std::endl
#else
#define announce_inExpression(type, exp, x)
#endif*/


//class Function
//{
//private:
//public:
//    static int evaluateExpression(Expression expression)
//    {
//
//    }
//};

bool var_defined(const string& var, std::map<string, Expression>& vars)
{
    if (vars.find(var) == vars.end())
        return false;
    else
        return true;
}


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
    std::map<string, Expression> variables{ {
        {"ans", Expression{}}
    } };
    

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
            /// TODO: may be Inefficient; use map with function pointers
            if (command == "help" || command == "h")
            {
                console.log(string{ "\nc{6}[Commands:]\n" }
                       +    "  c{12}[stop], c{12}[quit], c{12}[exit] (args: c{8}[None]):\n"
                       +    "    c{6}[--] Exit out of the program.\n\n"

                       +    "  c{14}[calculate], c{14}[calc] (args: c{10}[Expression]<string>):\n"
                       +    "    c{6}[--] Use the calculator.\n\n"

                       +    "  c{11}[store] (args: c{10}[Expression]<string>):\n"
                       +    "    c{6}[--] Store a variable to use later. You can always redefine a variable.\n\n"

                       +    "  c{13}[variables], c{13}[vars] (args: c{8}[None]):\n"
                       +    "    c{6}[--] See all stored variables.\n"
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
                try {
                    Expression e(arguments[0]);
                    variables["ans"] = e;
                    //e.simplify();
                    console.log("result: c{9}[" + e.expression + "]");
                }
                catch (lib::syntax_error e) {
                    console.error(e);
                }
            }

            else if (command == "store")
            { arguments = lib::get_arguments(user_input, 2);
                try {
                    string& varname = arguments[0];

                    Expression e;
                    if (lib::lower_case(varname) == "ans")
                        e = variables["ans"];
                    else
                        e = Expression{ arguments[1] };

                    
                    if (varname[0] == '_') {
                        throw(lib::store_error{ "Cannot start variable name with '_'" });
                    }
                    else if (char_in_constants(varname[0])) {
                        console.error("first letter of variable{ c{11}[" + arguments[0] + "] } cannot be a predefined constant.");
                    }
                    else if (char_in_numbers(varname[0]) ||
                        char_in_operators(varname[0]) ||
                       char_in_symbols(varname[0]))
                    {
                        console.error("first letter of variable{ c{11}[" + arguments[0] + "] } cannot be a number or symbol.");
                    }
                    else if (varname[1] != '_' && varname.size() > 1) {
                        throw(lib::store_error{ "Variable name can only be one char (may be followed by '_' for subscript)" });
                    }
                    else if (char_in_alphabet(varname[0]) ||
                        char_in_alphabetUpper(varname[0]))
                    {
                        if (var_defined(varname, variables))
                            variables[varname] = e;
                        else
                            variables.insert(std::pair<string, Expression>(varname, e));
                        console.log("c{11}[" + varname + "] = c{9}[" + variables[varname].expression + ']');
                    }
                }
                catch (lib::store_error e) {
                    console.error(e);
                }
                catch (lib::syntax_error e) {
                    console.error(e);
                }
            }

            else if (command == "variables" || command == "vars")
            {
                for (const auto& [var, exp] : variables)
                    console.log("c{11}[" + var + "] = c{9}[" + exp.expression + ']');
            }
            else if (command == "amogus") {
                console.log("When the Imposter is c{12}[sus!] c{14}[:flushed:]");
            }
            else {
                console.error("\"" + command + "\" is not a valid command.");
            }
        }
        catch (lib::argument_error e) {
            console.error(e);
        }
        console.log("");
    }

    PAUSE
}
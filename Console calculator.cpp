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
    string action;
    while (true)
    {
        std::cout << "What do you want to do?\nOptions:\n  this\n>";
        getline(std::cin, action);
        action = lower_case(action);

        if (action == "stop" || action == "quit")
        {
            std::cout << "goodbye!";
            exit(0);
        }
        else
        {
            try {
                Expression e(action);
                e.print();
            }
            catch (int e) {
                std::cout << '"' << action << "' cannot be evaluated";
            }
        }
    }
    //Expression e2("4-5");
    //e += e2;
    //std::cout << e.expression << std::endl;
    //e2.print();

    //Expression::print(e + "4x+7");
    //std::cout << Expression::simplify("2+5*2") << std::endl;
    //std::cout << integer(y) << std::endl;*/

    std::cout << "\n-END-";
}
#include "signals.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "switches.hpp"
#include "alu.hpp"
#include "mem.hpp"
#include "processor.hpp"
#include <iostream>
#include <string>

#define TAB "   "

using namespace std;

int print_case(string in, int success)
{
    cout << TAB << in << ": " << success << " " << (success ? "SUCCESS" : "FAIL") << endl;
    return success;
}

string bit_int(bit a)
{
    return std::to_string(static_cast<int>(a));
}

int t_nand()
{
    int s = 0;
    int t = 0;
    cout << "NAND Tests" << endl;
    for (bit a = 0; a < 2; a++)
    {
        for (bit b = 0; b < 2; b++)
        {
            s += print_case(bit_int(a) + " | " + bit_int(b), nand(a, b) == !(a & b));
            t++;
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    return s != t;
}

int t_not()
{
    int s = 0;
    int t = 0;
    cout << "NOT Tests" << endl;
    for (bit a = 0; a < 2; a++)
    {
        s += print_case("!" + bit_int(a), not_gate(a) == !a);
        t++;
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    return s != t;
}

void run_tests()
{   
    t_nand();
    t_not();
}

int main(void)
{
    run_tests();           
    return 0;
}
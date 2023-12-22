#include "signals.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "switches.hpp"
#include "alu.hpp"
#include "mem.hpp"
#include "processor.hpp"

#include <iostream>
#include <string>
#include <bitset>

#define TAB "   "

using namespace std;

int print_case(string in, int out, int expect)
{
    cout << TAB << in << ": " << out << " " << (out == expect ? "SUCCESS" : "FAIL") << endl;
    return out == expect;
}

string bit_str(bit a)
{
    return std::to_string(static_cast<int>(a));
}

string bus_str(bus b)
{
    return std::bitset<sizeof(bus) * 8>(b).to_string();
}

string bit_str_binary(bit a)
{
    return std::bitset<sizeof(bit) * 8>(a).to_string();
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
            s += print_case(bit_str(a) + " !& " + bit_str(b), nand(a, b), !(a & b));
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
        s += print_case("!" + bit_str(a), not_gate(a), !a);
        t++;
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    return s != t;
}

int t_and()
{
    int s = 0;
    int t = 0;
    cout << "AND Tests" << endl;
    for (bit a = 0; a < 2; a++)
    {
        for (bit b = 0; b < 2; b++)
        {
            s += print_case(bit_str(a) + " & " + bit_str(b), and_gate(a, b), (a & b));
            t++;
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    return s != t;
}

int t_or()
{
    int s = 0;
    int t = 0;
    cout << "OR Tests" << endl;
    for (bit a = 0; a < 2; a++)
    {
        for (bit b = 0; b < 2; b++)
        {
            s += print_case(bit_str(a) + " | " + bit_str(b), or_gate(a, b), (a | b));
            t++;
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    return s != t;
}

int t_xor()
{
    int s = 0;
    int t = 0;
    cout << "XOR Tests" << endl;
    for (bit a = 0; a < 2; a++)
    {
        for (bit b = 0; b < 2; b++)
        {
            s += print_case(bit_str(a) + " | " + bit_str(b), xor_gate(a, b), (a | b && !(a & b)));
            t++;
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    return s != t;
}

void run_gate_tests()
{   
    cout << "Testing Logic Gates" << endl;
    t_nand();
    t_not();
    t_and();
    t_or();
    t_xor();
    cout << "---------------------" << endl << endl;
}

void run_signal_tests()
{
    cout << "BUS Check" << endl;
    bus b = 0b0000000000000000;
    for (int i = 15; i >= 0; i--)
    {
        set_bit(b, i, 1);
        cout << TAB << bus_str(b) << endl;
    }
    if (b == 0b1111111111111111)
    {
        cout << TAB << "SUCCESS" << endl;
    }
    b = 0b0101010101010101;
    int s = 0;
    int t = 0;
    for (int i = 0; i < BUS_SIZE; i++)
    {
        bit a = get_bit(b, i);
        s += print_case("bit " + std::to_string(i) + ": " + bit_str(a), a, (i + 1) % 2);
        t++;
    }
    
    cout << "BIT Combination Check" << endl;
    bit c = combine_bits(1, 1, 1);
    cout << TAB << "combined: " << bit_str_binary(c) << endl;
    if (c == 0b00000111)
    {
        cout << TAB << "SUCCESS" << endl;
    }
    c = 0b01010101;
    s = 0;
    t = 0;
    for (int i = 0; i < COMB_BIT_SIZE; i++)
    {
        bit a = uncombine_bits(c, i);
        s += print_case("bit " + std::to_string(i) + ": " + bit_str(a), a, (i + 1) % 2);
        t++;
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    cout << "---------------------" << endl << endl;
}

void run_multibit_adder_test(bus a, bus b, bus expected)
{
    bus result = adder(a, b);
    print_case(bus_str(a) + " + " + bus_str(b), result, expected);
}

void run_arithmetic_tests()
{
    cout << "Testing Arithmetic Ops" << endl;
    
    // adder_b
    cout << "Adder Block Tests" << endl;
    int s = 0;
    int t = 0;
    for (bit a = 0; a < 2; a++)
    {
        for (bit b = 0; b < 2; b++)
        {
            for (bit c = 0; c < 2; c++)
            {
                s += print_case(bit_str(a) + " + " + bit_str(b) + " + " + bit_str(c), adder_b(a, b, c), (a + b + c));
                t++;
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    // adder
    cout << "Multibit Adder Tests" << endl;
    run_multibit_adder_test(0x0000, 0x0000, 0x0000);
    run_multibit_adder_test(0x0001, 0x0001, 0x0002);
    run_multibit_adder_test(0x0004, 0x0002, 0x0006);
    run_multibit_adder_test(0x0a04, 0x0b02, 0x0a04+0x0b02);
    
    cout << "---------------------" << endl << endl;
}




int main(void)
{
    run_gate_tests();        
    run_signal_tests();   
    run_arithmetic_tests();
    return 0;
}
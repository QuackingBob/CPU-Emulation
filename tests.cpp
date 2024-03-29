#include "signals.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "switches.hpp"
#include "alu.hpp"
#include "mem.hpp"
#include "mux.hpp"
#include "processor.hpp"
#include "progressbar.hpp"
#include "stats.hpp"
#include "components.hpp"

#include <iostream>
#include <string>
#include <bitset>
#include <chrono>

#define TAB "   "

using namespace std;

int print_case(string in, int out, int expect)
{
    cout << TAB << in << ": " << out << " exp: " << expect << " " << (out == expect ? "SUCCESS" : "FAIL") << endl;
    stats::success_count += out == expect;
    stats::case_count += 1;
    return out == expect;
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

int run_gate_bus_test(bus (*f)(bus, bus), bus a, bus b, bus expect, char rep)
{
    return print_case(bus_str(a) + " " + rep + " " + bus_str(b), f(a, b), expect);
}

void run_gate_tests()
{   
    cout << "Testing Logic Gates" << endl;
    t_nand();
    t_not();
    t_and();
    t_or();
    t_xor();
    cout << "Bus Tests" << endl;
    cout << "AND" << endl;
    int s = 0;
    int t = 0;
    s += run_gate_bus_test((&and_bus), 0x0001, 0x0000, 0x0000, '&'); t++;
    s += run_gate_bus_test((&and_bus), 0x0001, 0x0001, 0x0001, '&'); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    cout << "OR" << endl;
    s = 0;
    t = 0;
    s += run_gate_bus_test((&or_bus), 0x0001, 0x0001, 0x0001, '|'); t++;
    s += run_gate_bus_test((&or_bus), 0x0000, 0x0000, 0x0000, '|'); t++;
    s += run_gate_bus_test((&or_bus), 0x0001, 0x0000, 0x0001, '|'); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    cout << "XOR" << endl;
    s = 0;
    t = 0;
    s += run_gate_bus_test((&xor_bus), 0x0001, 0x0000, 0x0001, '^'); t++;
    s += run_gate_bus_test((&xor_bus), 0x0000, 0x0001, 0x0001, '^'); t++;
    s += run_gate_bus_test((&xor_bus), 0x0001, 0x0001, 0x0000, '^'); t++;
    s += run_gate_bus_test((&xor_bus), 0x0000, 0x0000, 0x0000, '^'); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

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
    bit c = combine_bits_three(1, 1, 1);
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

    cout << "Sign Extend Test" << endl;
    s = 0;
    t = 0;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(sign_extend(0b0000000000101010, 6)), sign_extend(0b0000000000101010, 6), (bus)0b1111111111101010); t++;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(sign_extend(0b0000000000101010, 7)), sign_extend(0b0000000000101010, 7), (bus)0b0000000000101010); t++;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(sign_extend(0b0000000000101010, 4)), sign_extend(0b0000000000101010, 4), (bus)0b1111111111111010); t++;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(sign_extend(0b0000000000101010, 3)), sign_extend(0b0000000000101010, 3), (bus)0b0000000000000010); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "zero Extend Test" << endl;
    s = 0;
    t = 0;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(zero_extend(0b0000000000101010, 6)), zero_extend(0b0000000000101010, 6), (bus)0b0000000000101010); t++;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(zero_extend(0b0000000000101010, 7)), zero_extend(0b0000000000101010, 7), (bus)0b0000000000101010); t++;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(zero_extend(0b0000000000101010, 4)), zero_extend(0b0000000000101010, 4), (bus)0b0000000000001010); t++;
    s += print_case(bus_str(0b0000000000101010) + "-> " + bus_str(zero_extend(0b0000000000101010, 3)), zero_extend(0b0000000000101010, 3), (bus)0b0000000000000010); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "---------------------" << endl << endl;
}

void run_multibit_adder_test(bus a, bus b, bus expected)
{
    bus result = adder(a, b);
    print_case(bus_str(a) + " + " + bus_str(b), result, expected);
}

void run_multibit_subtractor_test(bus a, bus b, bus expected)
{
    bus result = subtractor(a, b);
    print_case(bus_str(a) + " - " + bus_str(b), result, expected);
}

void run_logic_lt_zero_test(bus a, bus expected)
{
    bit result = lt_zero(a);
    print_case(bus_str(a) + " < 0", result, expected);
}

void run_logic_eq_zero_test(bus a, bus expected)
{
    bit result = eq_zero(a);
    print_case(bus_str(a) + " == 0", result, expected);
}

void run_logic_gt_zero_test(bus a, bus expected)
{
    bit result = gt_zero(a);
    print_case(bus_str(a) + " > 0", result, expected);
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

    // subtractor
    cout << "Subtractor Tests" << endl;
    run_multibit_subtractor_test(0x0000, 0x0000, 0x0000);
    run_multibit_subtractor_test(0x0001, 0x0001, 0x0000);
    run_multibit_subtractor_test(0x0004, 0x0002, 0x0002);
    run_multibit_subtractor_test(0x0a04, 0x0b02, 0x0a04-0x0b02);
    run_multibit_subtractor_test(0x0001, 0x0002, 0x0001-0x0002);

    //logic
    cout << "Logic Tests" << endl;

    // lt_zero
    cout << "LT Zero Tests" << endl;
    run_logic_lt_zero_test(0x0000, 0);
    run_logic_lt_zero_test(0x0001, 0);
    run_logic_lt_zero_test(0x0002, 0);
    run_logic_lt_zero_test(0xffff, 1);

    // eq_zero
    cout << "EQ Zero Tests" << endl;
    run_logic_eq_zero_test(0x0000, 1);
    run_logic_eq_zero_test(0x0001, 0);
    run_logic_eq_zero_test(0xf002, 0);
    // auto start = std::chrono::high_resolution_clock::now();
    // ProgressBar progressBar(65536);
    // s = 0;
    // t = 0;
    // for (bus i = -32768; i < 32767; i++)
    // {
    //     progressBar.update(i + 32768);
    //     s += eq_zero(i) == (i == 0);
    //     t++;
    // }
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); // microseconds if smaller
    // cout << TAB << s << "/" << t << " CASES PASSED. Took " << duration.count() << " milliseconds" << endl;

    // gt_zero
    cout << "GT Zero Tests" << endl;
    run_logic_gt_zero_test(0x0000, 0);
    run_logic_gt_zero_test(0x0001, 1);
    run_logic_gt_zero_test(0xf002, 0);

    cout << "---------------------" << endl << endl;
}

int run_select_bus_test(bit s, bus A, bus B, bus expected)
{
    bus result = select_bus(s, A, B);
    print_case(bit_str(s) + " ? " + bus_str(A) + " : " + bus_str(B), result, expected);
    return result == expected;
}

void run_switch_tests()
{
    cout << "Testing Switches" << endl;
    // selector
    cout << "Selector Tests" << endl;
    
    cout << "Select Bit" << endl;
    int s = 0;
    int t = 0;
    for (bit i = 0; i < 2; i++)
    {
        for (bit b0 = 0; b0 < 2; b0++)
        {
            for (bit b1 = 0; b1 < 2; b1++)
            {
                s += print_case(bit_str(i) + "? " + bit_str(b1) + " : " + bit_str(b0), selector(i, b1, b0), i?b1:b0);
                t++;
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Select Bus" << endl;
    s = 0;
    t = 0;
    s+=run_select_bus_test(0, 0x0000, 0x0000, 0x0000);t++;
    s+=run_select_bus_test(0, 0x0001, 0x0001, 0x0001);t++;
    s+=run_select_bus_test(0, 0x0004, 0x0002, 0x0002);t++;
    s+=run_select_bus_test(0, 0x0a04, 0x0b02, 0x0b02);t++;
    s+=run_select_bus_test(1, 0x0000, 0x0000, 0x0000);t++;
    s+=run_select_bus_test(1, 0x0001, 0x0001, 0x0001);t++;
    s+=run_select_bus_test(1, 0x0004, 0x0002, 0x0004);t++;
    s+=run_select_bus_test(1, 0x0a04, 0x0b02, 0x0a04);t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    cout << "---------------------" << endl << endl;
}

void run_alu_tests()
{
    cout << "Testing ALU" << endl;
    cout << "Testing Logic Unit" << endl;
    int s = 0;
    int t = 0;
    bus a = 0b0000100100010001;
    bus b = 0b0001000100100001;
    s += print_case("0, 0, " + bus_str(a) + " & " + bus_str(b), logic_unit(0, 0, a, b), a & b); t++;
    s += print_case("0, 1, " + bus_str(a) + " | " + bus_str(b), logic_unit(0, 1, a, b), a | b); t++;
    s += print_case("1, 0, " + bus_str(a) + " ^ " + bus_str(b), logic_unit(1, 0, a, b), xor_bus(a, b)); t++;
    s += print_case("1, 1, !" + bus_str(a), logic_unit(1, 1, a, b), inv_bus(a)); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Testing Arithmetic Unit" << endl;
    s = 0;
    t = 0;
    a = 0x0004;
    b = 0x0001;
    s += print_case("0, 0, " + bus_str(a) + " + " + bus_str(b), arithmetic_unit(0, 0, a, b), a + b); t++;
    s += print_case("0, 1, " + bus_str(a) + " + 1", arithmetic_unit(0, 1, a, b), a + 1); t++;
    s += print_case("1, 0, " + bus_str(a) + " - " + bus_str(b), arithmetic_unit(1, 0, a, b), a - b); t++;
    s += print_case("1, 1, " + bus_str(a) + " - 1", arithmetic_unit(1, 1, a, b), a - 1); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Testing Combined ALU unit" << endl;
    s = 0;
    t = 0;
    a = 0x0004;
    b = 0x0001;
    s += print_case("0, 0, 0, 0, 0, " + bus_str(a) + " & " + bus_str(b), alu(0, 0, 0, 0, 0, a, b), a & b); t++;
    s += print_case("1, 0, 1, 0, 0, " + bus_str(a) + " + " + bus_str(b), alu(1, 0, 1, 0, 0, a, b), a + b); t++;
    s += print_case("0, 1, 1, 0, 0, !" + bus_str(a), alu(0, 1, 1, 0, 0, a, b), inv_bus(a)); t++;
    s += print_case("1, 1, 0, 0, 1, " + bus_str(b) + " - " + bus_str(a), alu(1, 1, 0, 0, 1, a, b), b - a); t++;
    s += print_case("1, 1, 1, 1, 0, " + bus_str(a) + " - 1", alu(1, 1, 1, 1, 0, a, b), -1); t++;
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Testing Conditional Unit" << endl;
    s = 0;
    t = 0;
    a = 0x00ff;
    for (bit lt = 0; lt < 2; lt++)
    {
        for (bit eq = 0; eq < 2; eq++)
        {
            for (bit gt = 0; gt < 2; gt++)
            {
                bit cond = (lt && a < 0) || (eq && a == 0) || (gt && a > 0);
                s += print_case(bit_str(lt) + ", " + bit_str(eq) + ", " + bit_str(gt) + ", " + bus_str(a), condition(lt, eq, gt, a), cond); t++;
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "---------------------" << endl << endl;
}

void run_mux_tests()
{
    cout << "Testing Muxes" << endl;
    // selector
    cout << "Mux1to2 Tests" << endl;
    int s = 0;
    int t = 0;
    for (bit i = 0; i < 2; i++)
    {
        for (bit d0 = 0; d0 < 2; d0++)
        {
            for (bit d1 = 0; d1 < 2; d1++)
            {
                s += print_case(bit_str(i) + "? " + bit_str(d1) + " : " + bit_str(d0), mux1to2(d0, d1, i), i?d1:d0);
                t++;
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Mux2to4 Tests" << endl;
    s = 0;
    t = 0;
    for (bit s0 = 0; s0 < 2; s0++)
    {
        for (bit s1 = 0; s1 < 2; s1++)
        {
            for (bit d0 = 0; d0 < 2; d0++)
            {
                for (bit d1 = 0; d1 < 2; d1++)
                {
                    for (bit d2 = 0; d2 < 2; d2++)
                    {
                        for (bit d3 = 0; d3 < 2; d3++)
                        {
                            string label = bit_str(s0) + " " + bit_str(s1) + " " + bit_str(d0) + " " + bit_str(d1) + " " + bit_str(d2) + " " + bit_str(d3);
                            bit expect = 0;
                            switch (s0 + (s1 << 1))
                            {
                                case 0: expect = d0; break;
                                case 1: expect = d1; break;
                                case 2: expect = d2; break;
                                case 3: expect = d3; break;
                            }
                            s += print_case(label, mux2to4(d0, d1, d2, d3, s0, s1), expect);
                            t++;
                        }
                    }
                }
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Mux 3 to 8 bus test" << endl;
    s = 0;
    t = 0;
    cout << TAB << "[bus 0-7],s:0  1  2" << endl;
    for (bit s0 = 0; s0 < 2; s0++)
    {
        for (bit s1 = 0; s1 < 2; s1++)
        {
            for (bit s2 = 0; s2 < 2; s2++)
            {
                string label = "[01234567], " + bit_str(s0) + ", " + bit_str(s1) + ", " + bit_str(s2);
                bus expect = (s0 + (s1 << 1) + (s2 << 2));
                s += print_case(label, mux3to8bus(0,1,2,3,4,5,6,7,s0,s1,s2), expect);
                t++;
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "---------------------" << endl << endl;
}

void run_mem_tests()
{
    cout << "Testing Memory Components" << endl;

    cout << "Testing Latch" << endl;
    int s = 0;
    int t = 0;
    for (bit start = 0; start < 2; start++)
    {
        D_Latch latch(0);
        bit state;

        for (bit d = 0; d < 2; d++)
        {
            for (bit e = 0; e < 2; e++)
            {
                state = latch.get_q();
                latch.run(d, e);
                bit q = latch.get_q();
                bit q_bar = latch.get_q_bar();
                bit expect = e ? d : state;
                s += (expect == q && !expect == q_bar); t++;
                cout << TAB << bit_str(d) + " " + bit_str(e) + " " + bit_str(q) + " " + bit_str(q_bar) << ((expect == q && !expect == q_bar) ? " SUCCESS" : " FAIL") << endl;
            }
        }
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    stats::success_count += s;
    stats::case_count += t;

    cout << "Testing Flip-Flop" << endl;
    D_Flip_Flop flip(1);
    s = 0;
    t = 0;
    bit prev_clk = 1;
    bit prev_d = 0;
    bit clk;
    cout << TAB << "d c-c q q-" << endl;
    for(int i = 0; i < 10; i++) {
        clk = i % 2;
        bit d = (i % 3) % 2;
        bit prev_val = flip.output();
        bit prev_comp = flip.complement();
        flip.run(d, clk);
        bit val = flip.output();
        bit comp = flip.complement();

        bit trigger = (!prev_clk) && clk;
        bit expect = trigger ? prev_d : prev_val;
        s += (expect == val && !expect == comp); t++;
        cout << TAB << bit_str(d) + " " + bit_str(prev_clk) + " " + bit_str(clk) + " " + bit_str(val) + " " + bit_str(comp) << ((expect == val && !expect == comp) ? " SUCCESS" : " FAIL") << endl;
        prev_clk = clk;
        prev_d = d;
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    stats::success_count += s;
    stats::case_count += t;

    cout << "---------------------" << endl << endl;

    cout << "Testing Registers" << endl;

    Parallel_Load_Register reggie(0, 16);

    reg d = 0x0001;
    s = 0;
    t = 0;
    prev_clk = 1;
    reg prev_data = 0;
    bit load = 0;

    // cout << TAB << "d" << TAB << TAB << TAB << TAB << " c-c q" << endl;
    for(int i = 0; i < 16; i++) {

        if(i >= 8) {
            load = 1;
        }
        clk = i % 2;

        reg prev_val = reggie.get_output();

        reggie.run(load, d, clk);
        reg val = reggie.get_output();

        bit trigger = (!prev_clk) && clk && load;
        reg expect = trigger ? prev_data : prev_val;
        s += (expect == val); t++;
        cout << TAB << bus_str(d) + " " + bit_str(prev_clk) + " " + bit_str(clk) + " " + bus_str(val) + " " << ((expect == val) ? " SUCCESS" : " FAIL") << endl;
        prev_clk = clk;
        prev_data = d;

        d = d << 1;
    }

    cout << TAB << s << "/" << t << " CASES PASSED" << endl;
    stats::success_count += s;
    stats::case_count += t;

    cout << "---------------------" << endl << endl;



}

void run_component_tests()
{
    cout << "Testing Components" << endl;
    cout << "Testing Counter" << endl;
    program_counter counter(0);
    bit clk = 0;
    bus out;
    cout << "INCR Only" << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            clk = j % 2;
//            out = counter.update(1, 0, 0, clk);
            out = counter.run(0, 0, 1, clk, 0, 0);
        }
        cout << TAB << out << ", ";
    }
    cout << endl;

    cout << "No Change" << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            clk = j % 2;
            out = counter.run(1, 0, 0, clk, i % 2, 0);
        }
        cout << TAB << out << ", ";
    }
    cout << endl;

    cout << "Set Value" << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            clk = j % 2;
            out = counter.run(0, 1, 1, clk, 2 * i, 1);
        }
        cout << TAB << out << ", ";
    }
    cout << endl;

    cout << "Testing Eval Addr" << endl;
    eval_addr evaluate_address;
    int s = 0;
    int t = 0;
    bus ir = 0b1010101010101010;
    bus pc = 0x0003;
    bus sr1 = 0x0001;
    cout << TAB << "ir: " << bus_str(ir) << ", sr1: " << bus_str(sr1) << ", pc: " << bus_str(pc) << endl;
    for (bit i = 0; i < 8; i++)
    {
        bit s0 = uncombine_bits(i, 0);
        bit s1 = uncombine_bits(i, 1);
        bit s2 = uncombine_bits(i, 2);
        out = evaluate_address.run(s0, s1, s2, ir, sr1, pc);
        string label = bit_str(s0) + " " + bit_str(s1) + " " + bit_str(s2) + " -> " + bus_str(out);
        bus a;
        switch(i >> 1)
        {
            case 0: a = 0; break;
            case 1: a = sign_extend(ir, 6); break;
            case 2: a = sign_extend(ir, 9); break;
            case 3: a = sign_extend(ir, 11); break;
        }
        bus expect = a + (s0 ? sr1 : pc);
        s += print_case(label, out, expect); t++;
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "Reg File" << endl;
    reg_file register_file;
    s = 0;
    t = 0;
    for (bit ld = 0; ld < 2; ld++)
    {
        int output = 0;
        int expect = 0;
        for (bit i = 0; i < 8; i++)
        {
            bit s0 = uncombine_bits(i, 0), s1 = uncombine_bits(i, 1), s2 = uncombine_bits(i, 2);
            for (clk = 0; clk < 2; clk++)
            {
                register_file.update(ld, s0, s1, s2, i, clk);
            }
            output = 10 * output + static_cast<int>(register_file.sr1_load(s0, s1, s2));
            expect = 10 * expect + i;
        }
        expect = ld ? expect : 0;
        string label = "ld = " + bit_str(ld);
        s += print_case(label, output, expect); t++;
    }
    cout << TAB << s << "/" << t << " CASES PASSED" << endl;

    cout << "---------------------" << endl << endl;
}

int run_all_tests()
{
    run_gate_tests();
    run_signal_tests();
    run_arithmetic_tests();
    run_switch_tests();
    run_alu_tests();
    run_mux_tests();
    run_mem_tests();
    run_component_tests();
    return 0;
}

int main()
{
    stats::reset();
    double time;
    time_it(time, &run_all_tests);

    cout << stats::transistor_count << " Transistor Operations used" << endl;
    cout << stats::success_count << " CASES OUT OF " << stats::case_count << " CASES PASSED" << endl;
    cout << "Tests took " << time << " microseconds to run" << endl;
    return 0;
}
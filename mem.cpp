#include "mem.hpp"
#include "gates.hpp"
#include "mux.hpp"
#include <vector>

using namespace std;

// D_Latch
D_Latch::D_Latch(bit start)
{
    q = start;
    q_bar = not_gate(start);

}

void D_Latch::run(bit data, bit write_enable)
{
    bit s_bar = nand(data, write_enable);
    bit r_bar = nand(not_gate(data), write_enable);


    bit q_curr = q;
    bit q_bar_curr = q_bar;

    q = nand(s_bar, nand(r_bar, q_curr));
    q_bar = nand(r_bar, nand(s_bar, q_bar_curr));
}

bit D_Latch::get_q()
{
    return q;
}

bit D_Latch::get_q_bar()
{
    return q_bar;
}

// D_Flip_Flop
D_Flip_Flop::D_Flip_Flop(bit start) : master(start), slave(start)
{}

void D_Flip_Flop::run(bit data, bit clk)
{

    master.run(data, not_gate(clk));

    slave.run(master.get_q(), clk);
}

bit D_Flip_Flop::output()
{
    return slave.get_q();
}

bit D_Flip_Flop::complement()
{
    return slave.get_q_bar();
}

// Parallel_Load_Register
Parallel_Load_Register::Parallel_Load_Register(bit start, int length)
{
    for (int i = 0; i < length; i++)
    {
        reggie.push_back(new D_Flip_Flop(start));
    }
}

void Parallel_Load_Register::run(bit load, reg data, bit clk)
{
    for (int i = 0; i < reggie.size(); i++)
    {
        reggie[i]->run(mux1to2(reggie[i]->output(), get_bit(data,i), load), clk);
    }
}

reg Parallel_Load_Register::get_output()
{
    reg result = 0x0000;
    for (int i = 0; i < reggie.size(); i++)
    {
        set_bit(result, i, reggie[i]->output());
    }

    return result;
}

Parallel_Load_Register::~Parallel_Load_Register()
{
    for (auto flipFlop : reggie)
    {
        delete flipFlop;
    }
    reggie.clear();
}

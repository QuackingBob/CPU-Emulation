#include "mem.hpp"
#include "mux.cpp"
#include <vector>
using namespace std;

class D_Latch
{

private:
    bit q_bar;
    bit q;

public:
    D_Latch(bit start)
    {
        q = start;

        q_bar = not_gate(start);
    }

    void run(bit data, bit write_enable)
    {

        bit s_bar = nand(data, write_enable);
        bit r_bar = nand(not_gate(data), write_enable);

        q_bar = nand(r_bar, q);
        q = nand(s_bar, q_bar);
    }

    bit get_q()
    {
        return q;
    }

    bit get_q_bar()
    {
        return q_bar;
    }
};

class D_Flip_Flop
{

private:
    D_Latch master;
    D_Latch slave;

public:
    D_Flip_Flop(bit start) : master(start), slave(start)
    {}

    void run(bit data, bit clk)
    {

        master.run(data, not_gate(clk));

        slave.run(master.get_q(), clk);
    }

    bit output()
    {
        return slave.get_q();
    }

    bit complement()
    {
        return slave.get_q_bar();
    }
};

class Parallel_Load_Register
{

private:
    vector<D_Flip_Flop> reg;


public:
    Parallel_Load_Register(bit start, int length)
    {


        for (int i = 0; i < length; i++)
        {
            reg.push_back(*(new D_Flip_Flop(start)));
        }
    }

    void run(bit load, vector<bit> data, bit clk)
    {
        for (int i = 0; i < reg.size(); i++)
        {
            reg[i].run(mux1to2(reg[i].output(), data[i], load), clk);
        }
    }

    bus get_output()
    {
        bus result = 0x00;
        for (int i = 0; i < reg.size(); i++)
        {
            set_bit(result, i, reg[i].output());
        }

        return result;
    }
};

#include "mem.hpp"

class D_Latch
{

private:
    bit q_bar;
    bit q;

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

public:
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

    D_Flip_Flop(bit start)
    {

        master = new D_Latch(start);
        slave = new D_Latch(start);
    }

public:
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
};
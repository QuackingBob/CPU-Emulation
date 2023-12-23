#ifndef MEM_HPP
#define MEM_HPP

#include "gates.hpp"
#include "mux.hpp"

#include <vector>

using namespace std;
class D_Latch
{

private:
    bit q_bar;
    bit q;

public:
    D_Latch(bit start);
    void run(bit data, bit write_enable);
    bit get_q();
    bit get_q_bar();
};

class D_Flip_Flop
{

private:
    D_Latch master;
    D_Latch slave;

public:
    D_Flip_Flop(bit start);
    void run(bit data, bit clk);
    bit output();
    bit complement();
};

class Parallel_Load_Register
{

private:
    std::vector<D_Flip_Flop *> reggie;

public:
    Parallel_Load_Register(bit start, int length);
    void run(bit load, reg data, bit clk);
    reg get_output();
    ~Parallel_Load_Register();
};

#endif
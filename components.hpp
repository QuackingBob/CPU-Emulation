#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "mem.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "signals.hpp"

class program_counter
{
private:
    Parallel_Load_Register counter;

public:
    program_counter(bit state);
    bus update(bit load_pc, bit set, reg x, bit clk);
    bus pc_mux(bit s0, bit s1, bus main_bus, bus addr);
    bus load_pc(bit ld_pc, bus set, bit clk);
    bus run(bit s0, bit s1, bit ld_pc, bit clk, bus main_bus, bus addr);
};

class eval_addr
{
private:
    bus addr2mux(bit s0, bit s1, bus ir);
    bus addr1mux(bit s, bus sr1_out, bus pc);

public:
    bus run(bit addr1_s, bit addr2_s0, bit addr2_s1, bus ir, bus sr1_out, bus pc);
};

bus marmux(bit select, bus ir, bus eval_addr);

#endif

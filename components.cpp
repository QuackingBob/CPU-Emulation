#include "components.hpp"
#include "mem.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "signals.hpp"
#include "switches.hpp"

// Program Counter
program_counter::program_counter(bit state) : counter(state, 16)
{}

bus program_counter::update(bit load_pc, bit set, reg x, bit clk)
{
    bus curr = counter.get_output();
    bus input = select_bus(set, x, adder(curr, VCC));
    counter.run(and_gate(load_pc, not_gate(clk)), input, clk);
    return select_bus(clk, curr, GND);
}

bus program_counter::load_pc(bit ld_pc, bus set, bit clk)
{
    counter.run(ld_pc, set, clk);
    return counter.get_output();
}

bus program_counter::pc_mux(bit s0, bit s1, bus main_bus, bus addr)
{
    return select_bus(
            s1,
            main_bus,
            select_bus(
                    s0,
                    addr,
                    adder(counter.get_output(), 1)
                    )
            );
}

bus program_counter::run(bit s0, bit s1, bit ld_pc, bit clk, bus main_bus, bus addr)
{
    return load_pc(ld_pc, pc_mux(s0, s1, main_bus, addr), clk);
}
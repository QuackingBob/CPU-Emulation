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
    counter.run(not_gate(clk), input, clk);
    return select_bus(clk, curr, GND);
}
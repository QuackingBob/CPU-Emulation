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
};

#endif

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "mem.hpp"

class program_counter
{
private:
    Parallel_Load_Register counter;

public:
    program_counter(bus state);
    bus update(bit s, reg x, bit cl);
};

#endif

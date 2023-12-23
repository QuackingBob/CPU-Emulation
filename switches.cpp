#include "switches.hpp"

// a if s == 1 else b
bit selector(bit s, bit a, bit b)
{
    return or_gate(and_gate(s, a), and_gate(not_gate(s), b));
}

// a if s == 1 else b
bus select_bus(bit s, bus a, bus b)
{
    bus out;
    for (int i = 0; i < BUS_SIZE; i++)
    {
        set_bit(out, i, selector(s, get_bit(a, i), get_bit(b, i)));
    }
    return out;
}

bit switch_bit(bit s, bit d){
    bit c1 = and_gate(s, d);
    bit c2 = and_gate(not_gate(s), d);    
    return combine_bits_three(c1, c2, 0);;
}

bus switch_bus(bit s, bus d){
    return 0; // TODO: maybe this is useful, but no.
}
#include "arithmetics.hpp"
#include "stdio.h"

bit adder_b(bit a, bit b, bit c)
{
    bit xor_bc = xor_gate(b, c);
    bit l = and_gate(nand(a, xor_bc), nand(not_gate(a), not_gate(xor_bc)));
    bit h = nand(nand(a, xor_bc), nand(b, c));
    return combine_bits(0, h, l);
}

bus adder(bus A, bus B)
{
    bus result = 0;
    bit c = 0;
    for(int i = 0; i < BUS_SIZE; i++) {
        bit a = get_bit(A, i);
        bit b = get_bit(B, i);
        bit out = adder_b(a, b, c);
        c = get_bit(out, 1);
        a = get_bit(out, 0);
        set_bit(result, i, a);
    }
    return result;
}

bus subtractor(bus A, bus B)
{
    bus result = adder(adder(A, inv_bus(B)), 1);
    return result;
}
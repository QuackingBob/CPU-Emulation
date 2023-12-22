#include "arithmetics.hpp"

bit adder_b(bit a, bit b, bit c)
{
    bit xor_bc = xor_gate(b, c);
    bit d = and_gate(nand(a, xor_bc), nand(not_gate(a), not_gate(xor_bc)));
    bit h = nand(nand(a, xor_bc), nand(b, c));
    return combine_bits(h, d, 0);
}

bus adder(bus a, bus b)
{
    bus result = 0;
    bit c = 0;
    for(int i = 0; i < BUS_SIZE; i++) {
        bit a = get_bit(a, 0);
        bit b = get_bit(b, 0);
        bit out = adder_b(a, b, c);
        c = get_bit(out, 1);
        a = get_bit(out, 0);
        set_bit(result, i, a);
    }

    return result;
}
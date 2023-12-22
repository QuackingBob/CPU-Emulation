#include "arithmetics.hpp"

bit adder_b(bit a, bit b, bit c)
{
    bit xor_bc = xor_gate(b, c);
    bit l = and_gate(nand(a, xor_bc), nand(not_gate(a), not_gate(xor_bc)));
    bit h = nand(nand(a, xor_bc), nand(b, c));
    return combine_bits_three(0, h, l);
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

bit eq_zero(bus a)
{
    bit t = 0;
    for (int i = 0; i < BUS_SIZE / 2; i++)
    {
        combine_bits(t, or_gate(get_bit(a, 2 * i), get_bit(a, 2 * i + 1)), i);
    }
    for (int i = 0; i < COMB_BIT_SIZE / 2; i++)
    {
        combine_bits(t, or_gate(uncombine_bits(t, 2 * i), uncombine_bits(t, 2 * i + 1)), i);
    }
    for (int i = 0; i < COMB_BIT_SIZE / 4; i++)
    {
        combine_bits(t, or_gate(uncombine_bits(t, 2 * i), uncombine_bits(t, 2 * i + 1)), i);
    }
    for (int i = 0; i < COMB_BIT_SIZE / 8; i++)
    {
        combine_bits(t, or_gate(uncombine_bits(t, 2 * i), uncombine_bits(t, 2 * i + 1)), i);
    }
    return not_gate(uncombine_bits(t, 0));
}

bit lt_zero(bus a){
    return get_bit(a, BUS_SIZE - 1);
}

bit gt_zero(bus a){
    return and_gate(not_gate(lt_zero(a)), not_gate(eq_zero(a)));
}
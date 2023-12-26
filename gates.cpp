#include "gates.hpp"
#include "stats.hpp"
// bit gates

bit nmos_transistor(bit a, bit b)
{
    stats::transistor_count += 1;
    return a ? b : 0;
}

bit pmos_transistor(bit a, bit b)
{
    return a ? 0 : b;
}

bit nand(bit a, bit b)
{

    return VCC - (nmos_transistor(nmos_transistor(a, VCC), b)); // traditional diagram
    // return pmos_transistor(a, VCC) + pmos_transistor(b, VCC - pmos_transistor(a, VCC)) - nmos_transistor(a, nmos_transistor(b, VCC)) // hardware optimized circuit
}

bit not_gate(bit a)
{
    return nand(a, a);
}

bit and_gate(bit a, bit b)
{
    return not_gate(nand(a, b));
}

bit or_gate(bit a, bit b)
{
    return nand(not_gate(a), not_gate(b));
}

bit xor_gate(bit a, bit b)
{
    return and_gate(nand(a, b), or_gate(a, b));
}

bit xnor_gate(bit a, bit b)
{
    return  not_gate(xor_gate(a, b));
}

// bus gates

bus inv_bus(bus a)
{
    bus b;
    for(int i = 0; i < 16; i++){
        set_bit(b, i, not_gate(get_bit(a, i)));
    }
    return b;
}

bus and_bus(bus a, bus b)
{
    bus c;
    for(int i = 0; i < 16; i++){
        set_bit(c, i, and_gate(get_bit(a, i), get_bit(b, i)));
    }
    return c;
}

bus or_bus(bus a, bus b)
{
    bus c;
    for(int i = 0; i < 16; i++){
        set_bit(c, i, or_gate(get_bit(a, i), get_bit(b, i)));
    }
    return c;
}

bus xor_bus(bus a, bus b)
{
    bus c;
    for(int i = 0; i < 16; i++){
        set_bit(c, i, xor_gate(get_bit(a, i), get_bit(b, i)));
    }
    return c;
}

// Tri State Buffer

bit tri_state_buffer(bit input, bit current, bit gate)
{
    return pmos_transistor(gate, current) + nmos_transistor(gate, input);
}

bus tri_state_buffer_bus(bus input, bus current, bit gate)
{
    bus result;

    for(int i = 0; i < 16; i++)
    {

        set_bit(result, i, tri_state_buffer(get_bit(input, i), get_bit(current, i), gate));

    }

    return result;
}

// Logical Bus Gates:

bit and4(bit a1, bit a2, bit a3, bit a4) {

    return and_gate(a1, and_gate(a2, and_gate(a3, a4)));
}

bit and8(bit a1, bit a2, bit a3, bit a4, bit a5, bit a6, bit a7, bit a8) {

    return and_gate(and4(a1, a2, a3, a4), and4(a5, a6, a7, a8));
}

bit and16(bus a16) {

    bit out1 = and8(get_bit(a16, 0), get_bit(a16, 1), get_bit(a16, 2), get_bit(a16, 3), get_bit(a16, 4), get_bit(a16, 5), get_bit(a16, 6), get_bit(a16, 7));
    bit out2 = and8(get_bit(a16, 8), get_bit(a16, 9), get_bit(a16, 10), get_bit(a16, 11), get_bit(a16, 12), get_bit(a16, 13), get_bit(a16, 14), get_bit(a16, 15));

    return and_gate(out1, out2);
}

bit normalize(bit a)
{
    return !!a;
}
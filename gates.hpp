#include "signals.hpp"

bit nmos_transistor(bit a, bit b)
{
    return a ? b : 0;
}

bit pmos_transistor(bit a, bit b)
{
    return a ? 0 : b;
}

bit nand(bit a, bit b)
{
    return VCC - (nmos_transistor(nmos_transistor(a, VCC), b)); // traditional diagram
    // return pmos_transistor(a, VCC) + pmos_transistor(b, VCC) - nmos_transistor(a, nmos_transistor(b, VCC));
    // return pmos_transistor(a, VCC) + pmos_transistor(b, VCC - pmos_transistor(a, VCC)) - nmos_transistor(a, nmos_transistor(b, VCC))
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
#include "signals.hpp"

bit transistor(bit a, bit b)
{
    return a ? b : 0;
}

bit nand(bit a, bit b)
{
    return VCC - (transistor(transistor(a, VCC), b));
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
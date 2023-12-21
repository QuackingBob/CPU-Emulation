#include "signals.hpp"

bit transistor(bit a, bit b)
{
    return a ? b : 0;
}

bit nand(bit a, bit b)
{
    return VCC - (transistor(transistor(a, VCC), b));
}
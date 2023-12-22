#include "signals.hpp"

int check_index(int index, int size)
{
    if (index < 0 || index >= size) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return 1;
    }
    return 0;
}

bit get_bit(bus b, int index) {
    check_index(index, BUS_SIZE);
    return (b >> index) & 0x0001;
}

void set_bit(bus &b, int index, bit a)
{
    check_index(index, BUS_SIZE);
    if (a)
        b |= (1 << index);
    else
        b &= ~(1 << index);
}

// think of this as an 8 bit bus
bit combine_bits_three(bit a, bit b, bit c)
{
    return c | (b << 1) | (a << 2);
}

void combine_bits(bit &a, bit b, int index)
{
    a |= (b << index);
}

bit uncombine_bits(bit a, int index)
{
    check_index(index, COMB_BIT_SIZE);
    return (a >> index) & 0x0001;
}
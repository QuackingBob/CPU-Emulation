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

// Done using wires, not gates so represented this way
bus sign_extend(bus b, int len)
{
    bit a = get_bit(b, len - 1);
    for (int i = len; i < BUS_SIZE; i++)
    {
        set_bit(b, i, a);
    }
    return b;
}

// Done using wires, not gates so represented this way
bus zero_extend(bus b, int len)
{
    for (int i = len; i < BUS_SIZE; i++)
    {
        set_bit(b, i, 0);
    }
    return b;
}

string bit_str(bit a)
{
    return std::to_string(static_cast<int>(a));
}

string bus_str(bus b)
{
    return std::bitset<sizeof(bus) * 8>(b).to_string();
}

string bit_str_binary(bit a)
{
    return std::bitset<sizeof(bit) * 8>(a).to_string();
}
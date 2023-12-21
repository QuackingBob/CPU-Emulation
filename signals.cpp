#include "signals.hpp"

int check_index(int index)
{
    if (index < 0 || index > 15) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return 1;
    }
    return 0;
}

bit get_bit(bus b, int index) {
    check_index(index);
    return (b >> index) & 0x0001;
}

void set_bit(bus &b, int index, bit a)
{
    check_index(index);
    if (a)
        b |= (1 << index);
    else
        b &= ~(1 << index);
}
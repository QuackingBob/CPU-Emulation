#include "decoder.hpp"
#include "gates.hpp"

void decode(reg address)
{
    for (int i = 0; i < MAX_INT; i++)
    {
        reg temp = address;
        for (int j = BUS_SIZE - 1; j >= 0; j--)
        {
            int result = i & 0x00000001;
            if (!result)
            {
                set_bit(temp, j, not_gate(get_bit(temp, j)));
            }
        }
        decoded[i] = and16(temp);
    }
}

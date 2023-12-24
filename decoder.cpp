#include "decoder.hpp"
#include "gates.hpp"

void decode(reg address)
{

    for(int i = 0; i < 65536; i++) {

        reg temp = address;

        for(int j = 15; j >= 0; j--) {

            int result = i & 0x00000001;

            if(!result) {

                set_bit(temp, j, not_gate(get_bit(temp, j)));

            }


        }

        decoded[i] = and16(temp);
    }
}

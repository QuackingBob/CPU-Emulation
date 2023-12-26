#ifndef GATES_HPP
#define GATES_HPP

#include "signals.hpp"
#include "stats.hpp"

bit nmos_transistor(bit a, bit b);
bit pmos_transistor(bit a, bit b);
bit nand(bit a, bit b);
bit not_gate(bit a);
bit and_gate(bit a, bit b);
bit or_gate(bit a, bit b);
bit xor_gate(bit a, bit b);
bit xnor_gate(bit a, bit b);

bus inv_bus(bus a);
bus and_bus(bus a, bus b);
bus or_bus(bus a, bus b);
bus xor_bus(bus a, bus b);

bit tri_state_buffer(bit input, bit current, bit gate);
bus tri_state_buffer_bus(bus input, bus current, bit gate);
bit and4(bit a1, bit a2, bit a3, bit a4);
bit and8(bit a1, bit a2, bit a3, bit a4, bit a5, bit a6, bit a7, bit a8);
bit and16(bus a16);

bit normalize(bit a);

#endif
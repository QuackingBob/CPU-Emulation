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

bus inv_bus(bus a);
bus and_bus(bus a, bus b);
bus or_bus(bus a, bus b);
bus xor_bus(bus a, bus b);

#endif
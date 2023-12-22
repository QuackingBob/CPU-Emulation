#ifndef SWITCHES_HPP
#define SWITCHES_HPP

#include "gates.hpp"

bit selector(bit s, bit a, bit b);
bus select_bus(bit s, bus a, bus b);
bit switch_bit(bit s, bit d);
bus switch_bus(bit s, bus d);

#endif
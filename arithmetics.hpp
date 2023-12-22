#ifndef ARITHMETICS_HPP
#define ARITHMETICS_HPP

#include "signals.hpp"
#include "gates.hpp"

bit adder_b(bit a, bit b, bit c); // returns a group of bits. see signals.cpp
bus adder(bus a, bus b);
bus subtractor(bus a, bus b);
bit eq_zero(bus a);
bit lt_zero(bus a);
bit gt_zero(bus a);

#endif
#ifndef ALU_HPP
#define ALU_HPP

#include "gates.hpp"
#include "signals.hpp"
#include "switches.hpp"
#include "arithmetics.hpp"

bus logic_unit(bit op0, bit op1, bus a, bus b);
bus arithmetic_unit(bit op0, bit op1, bus a, bus b);
bus alu(bit sel, bit op1, bit op0, bit zl, bit sw, bus a, bus b);

#endif
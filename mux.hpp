#ifndef MUX_HPP
#define MUX_HPP

#include "gates.hpp"

bit mux1to2(bit zero, bit one, bit select);
bit mux2to4(bit zero, bit one, bit two, bit three, bit select0, bit select1);
bus mux1to2bus(bus zero, bus one, bit select);
bus mux2to4bus(bus zero, bus one, bus two, bus three, bit select0, bit select1);
bus mux3to8bus(bus b0, bus b1, bus b2, bus b3, bus b4, bus b5, bus b6, bus b7, bit s0, bit s1, bit s2);

#endif
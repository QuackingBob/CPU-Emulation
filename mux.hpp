#ifndef MUX_HPP
#define MUX_HPP

#include "gates.hpp"

bit mux1to2(bit zero, bit one, bit select);
bit mux2to4(bit zero, bit one, bit two, bit three, bit select0, bit select1);
bus mux1to2bus(bus zero, bus one, bit select);
bus mux2to4bus(bus zero, bus one, bus two, bus three, bit select0, bit select1);

#endif
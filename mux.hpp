#ifndef MUX_HPP
#define MUX_HPP

#include "gates.hpp"

bit mux1to2(bit zero, bit one, bit select);
bit mux2to4(bit zero, bit one, bit two, bit three, bit select0, bit select1);

#endif
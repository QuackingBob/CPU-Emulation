#include "mux.hpp"


bit mux1to2(bit zero, bit one, bit select) {

    return or_gate(and_gate(zero, not_gate(select)), and_gate(one, select));
}

bit mux2to4(bit zero, bit one, bit two, bit three, bit select0, bit select1) {

    bit s0 = and_gate(zero, and_gate(not_gate(select0), not_gate(select1)));

    bit s1 = and_gate(one, and_gate(not_gate(select0), select1));

    bit s2 = and_gate(two, and_gate(select0, not_gate(select1)));

    bit s3 = and_gate(three, and_gate(select0, select1));

    return or_gate(s0, or_gate(s1, or_gate(s2, s3)));
}

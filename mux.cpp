#include "mux.hpp"
#include "switches.hpp"


bit mux1to2(bit zero, bit one, bit select) {
    return selector(select, one, zero); // same purpose, diff names
    // return or_gate(and_gate(zero, not_gate(select)), and_gate(one, select));
}

bit mux2to4(bit zero, bit one, bit two, bit three, bit select0, bit select1) {

    // bit s0 = and_gate(zero, and_gate(not_gate(select0), not_gate(select1)));
    // bit s1 = and_gate(one, and_gate(not_gate(select0), select1));
    // bit s2 = and_gate(two, and_gate(select0, not_gate(select1)));
    // bit s3 = and_gate(three, and_gate(select0, select1));
    // return or_gate(s0, or_gate(s1, or_gate(s2, s3)));

    return  mux1to2(
                mux1to2(
                    mux1to2(zero, one, select0),
                    two,
                    select1
                ),
                three,
                and_gate(select0, select1)
            );
}

bus mux1to2bus(bus zero, bus one, bit select) {
    return select_bus(select, one, zero);
}

bus mux2to4bus(bus zero, bus one, bus two, bus three, bit select0, bit select1) {
    return  mux1to2bus(
                mux1to2bus(
                    mux1to2bus(zero, one, select0),
                    two,
                    select1
                ),
                three,
                and_gate(select0, select1)
            );
}
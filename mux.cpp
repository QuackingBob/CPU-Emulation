#include "mux.hpp"

class Mux1To2 {

    Mux1To2() {

    }

public:
    bit output(bit zero, bit one, bit select) {

        return or_gate(and_gate(zero, not_gate(select)), and_gate(one, select));
    }
};

class Mux2To4
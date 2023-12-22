#include "alu.hpp"

/*
op1	op0	output
0	0	A and B
0	1	A or B
1	0	A xor B
1	1	invert A
*/
bus logic_unit(bit op0, bit op1, bus a, bus b)
{
    return select_bus(
        nand(op0, op1),
        select_bus(
            op0,
            or_bus(a, b),
            select_bus(
                op1,
                xor_bus(a, b),
                and_bus(a, b)
            )
        ),
        inv_bus(a)
    );
}


#include "alu.hpp"

/*
op1	op0	output
0	0	A and B
0	1	A or B
1	0	A xor B
1	1	invert A
*/
bus logic_unit(bit op1, bit op0, bus a, bus b)
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

/*
op1	op0	output
0	0	A + B
0	1	A + 1
1	0	A - B
1	1	A - 1
*/
bus arithmetic_unit(bit op1, bit op0, bus a, bus b)
{
    return select_bus(
        nand(op0, op1),
        select_bus(
            op0,
            adder(a, VCC),
            select_bus(
                op1,
                subtractor(a, b),
                adder(a, b)
            )
        ),
        subtractor(a, VCC)
    );
}
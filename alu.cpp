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

/*
sel : logic or arithmetic unit

Input	Output
sel	op1	op0	
0	0	0	A and B
0	0	1	A or B
0	1	0	A xor B
0	1	1	invert A
1	0	0	A + B
1	1	0	A - B
1	0	1	A + 1
1	1	1	A - 1

if zl : zeros left operand
if sw : swaps operands
*/
bus alu(bit sel, bit op1, bit op0, bit zl, bit sw, bus a, bus b)
{
    bus l = select_bus(
                zl,
                GND,
                select_bus(
                    sw,
                    b,
                    a
                )
            );
    bus r = select_bus(
                sw,
                a,
                b
            );
    return select_bus(
        sel,
        arithmetic_unit(op1, op0, l, r),
        logic_unit(op1, op0, l, r)
    );
}

bit condition(bit lt, bit eq, bit gt, bus x)
{
    return or_gate(
        or_gate(
            and_gate(eq, eq_zero(x)),
            and_gate(gt, gt_zero(x))
        ),
        and_gate(lt, lt_zero(x))
    );
}
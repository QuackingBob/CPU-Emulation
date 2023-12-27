//
// Created by vvk on 12/26/23.
//

#include "controller.hpp"

Controller::Controller()
{
    reg start_addr = 18;
    current_state = rom.read(start_addr);
}

ROM_SIGNALS Controller::get_state()
{
    return current_state;
}

void Controller::next(INPUT_SIGNALS input, instruction_register ir)
{
    reg next_addr = current_state.J;

    bit C0 = current_state.COND0;
    bit C1 = current_state.COND1;
    bit C2 = current_state.COND2;

    set_bit(next_addr, 14, or_gate(and4(not_gate(C2), not_gate(C1), C0, input.R), get_bit(next_addr, 14)));
    set_bit(next_addr, 13, or_gate(and4(not_gate(C2), C1, not_gate(C0), input.BEN), get_bit(next_addr, 13)));

    reg ird_addr = 0;

    reg inst = ir.get_ir();

    set_bit(ird_addr, 15, get_bit(inst, 3));

    set_bit(ird_addr, 14, get_bit(inst, 2));

    set_bit(ird_addr, 13, get_bit(inst, 1));

    set_bit(ird_addr, 12, get_bit(inst, 0));

    reg next_state = mux1to2bus(next_addr, ird_addr, current_state.IRD);

    current_state = rom.read(next_state);

}



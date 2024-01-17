#include "processor.hpp"

int Processor::tick() {
    bus pc_out = pc.run(0, 0, 1, clock, 0, 0); // tick the program counter todo: need to implement jump if j flag is set
    //get memory values from ram
    // input to control unit
    bus I; // instruction register
    bus A; // current value of the A register
    bus D; // current value of the D register
    bus star_A; // current value in ram at the value of the A register

    // call controller with these inputs
    // get instruction from rom at program counter

    // control unit outputs
    bus R; // control unit output
    bus a; // flag a register
    bus d; // flag d register
    bus star_a; // flag write R to ram at A register
    bus j; // flag jump, sets the program counter to the value of the A register
    // set the values of the registers in rom


    clock = not_gate(clock);
    return 0;
}

int Processor::reset_state()
{
    while (state -> state_count != 18)
    {
        state = state -> transition_state;
    }
}

int Processor::init_state_graph()
{

}

Processor::~Processor()
{
    // state_transition *next = NULL;
    // while (next -> s)
}

state_transition* update_state(int r_bar, state_transition *state)
{
    if (state -> transition_cond(r_bar))
        return state -> transition_state;
    return state;
}
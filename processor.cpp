#include "processor.hpp"

int Processor::tick() {
    bus pc_out = pc.run(clock /* stuff goes here, clock is the 3rd argument */ ); // tick the program counter or set it to the state returned by the
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
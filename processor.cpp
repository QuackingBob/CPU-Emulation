#include "processor.hpp"

int Processor::tick()
{
    bus pc_out = pc.run(0, 0, 1, clock, 0, 0); // tick the program counter todo: need to implement jump if j flag is set
    // get memory values from ram
    //  input to control unit
    bus I;      // instruction register
    bus A;      // current value of the A register
    bus D;      // current value of the D register
    bus star_A; // current value in ram at the value of the A register

    // call controller with these inputs
    // get instruction from rom at program counter

    // control unit outputs
    bus R;      // control unit output
    bus a;      // flag a register
    bus d;      // flag d register
    bus star_a; // flag write R to ram at A register
    bus j;      // flag jump, sets the program counter to the value of the A register
    // set the values of the registers in rom

    clock = not_gate(clock);
    return 0;
}

int Processor::reset_state()
{
    state = state->state_map["S18"];
}

int Processor::init_state_graph()
{
    auto sigs = signals;
    auto control_sigs = control_signals;

    state_transition *s18 = new_state(18);
    s18->transition = [&s18]() -> state_transition *
    {
        return s18->state_map["S33"];
    };

    state_transition *s33 = new_state(33);
    s33->transition = [&s33, &sigs]() -> state_transition *
    {
        if (sigs.R)
            return s33->state_map["S35"];
        else
            return s33->state_map["S33"];
    };

    state_transition *s35 = new_state(35);
    s35->transition = [&s35, &sigs]() -> state_transition *
    {
        return s35->state_map["S32"];
    };

    state_transition *s32 = new_state(32);
    s32->transition = [&s32, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s32;
    };

    state_transition *s1 = new_state(1);
    s1->transition = [&s1, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s1;
    };

    state_transition *s5 = new_state(5);
    s5->transition = [&s5, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s5;
    };

    state_transition *s9 = new_state(9);
    s9->transition = [&s9, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s9;
    };

    state_transition *s15 = new_state(15);
    s15->transition = [&s15, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s15;
    };

    state_transition *s28 = new_state(28);
    s28->transition = [&s28, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s28;
    };

    state_transition *s30 = new_state(30);
    s30->transition = [&s30, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s30;
    };

    state_transition *s14 = new_state(14);
    s14->transition = [&s14, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s14;
    };

    state_transition *s10 = new_state(10);
    s10->transition = [&s10, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s10;
    };
    
    state_transition *s24 = new_state(24);
    s24->transition = [&s24, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s24;
    };

    state_transition *s6 = new_state(6);
    s6->transition = [&s6, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s6;
    };

    state_transition *s2 = new_state(2);
    s2->transition = [&s2, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s2;
    };

    state_transition *s25 = new_state(25);
    s25->transition = [&s25, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s25;
    };

    state_transition *s27 = new_state(27);
    s27->transition = [&s27, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s27;
    };

    state_transition *s26 = new_state(26);
    s26->transition = [&s26, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s26;
    };

    state_transition *s11 = new_state(11);
    s11->transition = [&s11, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s11;
    };

    state_transition *s29 = new_state(29);
    s29->transition = [&s29, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s29;
    };

    state_transition *s7 = new_state(7);
    s7->transition = [&s7, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s7;
    };

    state_transition *s31 = new_state(31);
    s31->transition = [&s31, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s31;
    };

    state_transition *s3 = new_state(3);
    s3->transition = [&s3, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s3;
    };

    state_transition *s23 = new_state(23);
    s23->transition = [&s23, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s23;
    };

    state_transition *s16 = new_state(16);
    s16->transition = [&s16, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s16;
    };

    state_transition *s0 = new_state(0);
    s0->transition = [&s0, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s0;
    };

    state_transition *s22 = new_state(22);
    s22->transition = [&s22, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s22;
    };

    state_transition *s12 = new_state(12);
    s12->transition = [&s12, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s12;
    };

    state_transition *s4 = new_state(4);
    s4->transition = [&s4, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s4;
    };

    state_transition *s21 = new_state(21);
    s21->transition = [&s21, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s21;
    };

    state_transition *s20 = new_state(20);
    s20->transition = [&s20, &control_sigs]() -> state_transition *
    {
        // TODO Figure out wtf is going on here
        return s20;
    };
}

Processor::~Processor()
{
}

state_transition *new_state(int state_num)
{
    state_transition *s = (state_transition *)malloc(sizeof(state_transition));
    s->state_count = state_num;
    string state_name = "S" + std::to_string(state_num);
    s->state_map.insert({state_name, s});
    return s;
}
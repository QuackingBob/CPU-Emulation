#include "components.hpp"
#include "mem.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "signals.hpp"
#include "switches.hpp"

// Program Counter
program_counter::program_counter(bit state) : counter(state, 16)
{}

bus program_counter::update(bit load_pc, bit set, reg x, bit clk)
{
    bus curr = counter.get_output();
    bus input = select_bus(set, x, adder(curr, VCC));
    counter.run(and_gate(load_pc, not_gate(clk)), input, clk);
    return select_bus(clk, curr, GND);
}

bus program_counter::load_pc(bit ld_pc, bus set, bit clk)
{
    counter.run(ld_pc, set, clk);
    return counter.get_output();
}

bus program_counter::pc_mux(bit s0, bit s1, bus main_bus, bus addr)
{
    return select_bus(
            s1,
            main_bus,
            select_bus(
                    s0,
                    addr,
                    adder(counter.get_output(), 1)
                    )
            );
}

bus program_counter::run(bit s0, bit s1, bit ld_pc, bit clk, bus main_bus, bus addr)
{
    return load_pc(ld_pc, pc_mux(s0, s1, main_bus, addr), clk);
}

// Eval address
bus eval_addr::addr2mux(bit s0, bit s1, bus ir)
{
    bus d2 = sign_extend(ir, 11); // [10:0]
    bus d1 = sign_extend(ir, 9); // [8:0]
    bus d0 = sign_extend(ir, 6); // [5:0]
    return mux2to4(GND, d0, d1, d2, s0, s1);
}

bus eval_addr::addr1mux(bit s, bus sr1_out, bus pc)
{
    return mux1to2(pc, sr1_out, s);
}

bus eval_addr::run(bit addr1_s, bit addr2_s0, bit addr2_s1, bus ir, bus sr1_out, bus pc)
{
    // TODO: Figure out what + means (or? add?) i think or
    return or_bus(addr1mux(addr1_s, sr1_out, pc), addr2mux(addr2_s0, addr2_s1, ir));
}

// marmux
bus marmux(bit select, bus ir, bus eval_addr)
{
    return mux1to2(eval_addr, zero_extend(ir, 8), select); // zext [7:0]
}
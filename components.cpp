#include "components.hpp"
#include "mem.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "signals.hpp"
#include "switches.hpp"

#include <bitset>
#include <string>

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
    bus d2 = sign_extend(ir, 11); // SEXT [10:0]
    bus d1 = sign_extend(ir, 9); // SEXT [8:0]
    bus d0 = sign_extend(ir, 6); // SEXT [5:0]
    return mux2to4bus(GND, d0, d1, d2, s0, s1);
}

bus eval_addr::addr1mux(bit s, bus sr1_out, bus pc)
{
    return mux1to2bus(pc, sr1_out, s);
}

bus eval_addr::run(bit addr1_s, bit addr2_s0, bit addr2_s1, bus ir, bus sr1_out, bus pc)
{
    // TODO: Figure out what + means (or? add?)
    return adder(addr1mux(addr1_s, sr1_out, pc), addr2mux(addr2_s0, addr2_s1, ir));
}

// marmux
bus marmux(bit select, bus ir, bus eval_addr)
{
    return mux1to2bus(eval_addr, zero_extend(ir, 8), select); // ZEXT [7:0]
}

// sr2mux
bus sr2mux(bit select, bus ir, bus sr2_out)
{
    return mux1to2bus(sr2_out, sign_extend(ir, 5), select); //  SEXT [4:0]
}

// register file
reg_file::reg_file()
{
    registers = new Parallel_Load_Register*[num_registers];
    for (int i = 0; i < num_registers; i++)
    {
        registers[i] = new Parallel_Load_Register(0, BUS_SIZE);
    }
}

void reg_file::update(bit ld_reg, bit dr_0, bit dr_1, bit dr_2, bus data, bit clk)
{
    // this is just a lot of repeated gates, i just automates the placement of wires
    for (bit i = 0; i < num_registers; i++)
    {
        registers[i] -> run(
            and_gate(
                ld_reg,
                and_gate(
                    xnor_gate(uncombine_bits(i, 2), dr_2),
                    and_gate(
                        xnor_gate(uncombine_bits(i, 1), dr_1),
                        xnor_gate(uncombine_bits(i, 0), dr_0)
                    )
                )
            ),
            data,
            clk
        );
    }
}

bus reg_file::sr1_load(bit sr1_0, bit sr1_1, bit sr1_2)
{
    return mux3to8bus(
        registers[0] -> get_output(),
        registers[1] -> get_output(),
        registers[2] -> get_output(),
        registers[3] -> get_output(),
        registers[4] -> get_output(),
        registers[5] -> get_output(),
        registers[6] -> get_output(),
        registers[7] -> get_output(),
        sr1_0,
        sr1_1,
        sr1_2
    );
}

bus reg_file::sr2_load(bit sr2_0, bit sr2_1, bit sr2_2)
{
    return mux3to8bus(
        registers[0] -> get_output(),
        registers[1] -> get_output(),
        registers[2] -> get_output(),
        registers[3] -> get_output(),
        registers[4] -> get_output(),
        registers[5] -> get_output(),
        registers[6] -> get_output(),
        registers[7] -> get_output(),
        sr2_0,
        sr2_1,
        sr2_2
    );
}

reg_file::~reg_file()
{
    for (int i = 0; i < num_registers; i++)
    {
        delete registers[i];
    }

    delete[] registers;
}

// data bus
data_bus::data_bus(bus init) : data(init)
{}

void data_bus::update_bus(bus value)
{
    data = value;
}

bus data_bus::read_bus()
{
    return data;
}

// main wiring object
main_wiring::main_wiring()
{
    control_signals = (bit *) calloc(num_signals, sizeof(bit));
}

void main_wiring::write_signal(CONTROL_SIG signal, bit value)
{
    control_signals[signal] = value;
}

bit main_wiring::read_signal(CONTROL_SIG signal)
{
    return control_signals[signal];
}

bit& main_wiring::operator[](CONTROL_SIG signal) 
{
    return control_signals[signal];
}

main_wiring::~main_wiring()
{
    free(control_signals);
}
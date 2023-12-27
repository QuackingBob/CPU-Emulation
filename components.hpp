#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "mem.hpp"
#include "gates.hpp"
#include "arithmetics.hpp"
#include "signals.hpp"

class program_counter
{
private:
    Parallel_Load_Register counter;

public:
    program_counter(bit state);
    bus update(bit load_pc, bit set, reg x, bit clk);
    bus pc_mux(bit s0, bit s1, bus main_bus, bus addr);
    bus load_pc(bit ld_pc, bus set, bit clk);
    bus run(bit s0, bit s1, bit ld_pc, bit clk, bus main_bus, bus addr);
};

class eval_addr
{
private:
    bus addr2mux(bit s0, bit s1, bus ir);
    bus addr1mux(bit s, bus sr1_out, bus pc);

public:
    bus run(bit addr1_s, bit addr2_s0, bit addr2_s1, bus ir, bus sr1_out, bus pc);
};

bus marmux(bit select, bus ir, bus eval_addr);
bus sr2mux(bit select, bus ir, bus sr2_out);

class reg_file
{
private:
    Parallel_Load_Register **registers;
    const static int num_registers = 8;

public:
    reg_file();
    void update(bit ld_reg, bit dr_0, bit dr_1, bit dr_2, bus data, bit clk);
    bus sr1_load(bit sr1_0, bit sr1_1, bit sr1_2);
    bus sr2_load(bit sr2_0, bit sr2_1, bit sr2_2);
    ~reg_file();
};

class data_bus
{
private:
    bus data;

public:
    data_bus(bus init);
    void update_bus(bus value);
    bus read_bus();
};

class main_wiring
{
private:
    bit *control_signals;
    const static int num_signals = 25;

public:
    main_wiring();
    void write_signal(CONTROL_SIG signal, bit value);
    bit read_signal(CONTROL_SIG signal);
    bit& operator[](CONTROL_SIG signal);
    ~main_wiring();
};

#endif

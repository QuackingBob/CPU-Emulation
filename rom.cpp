//
// Created by vvk on 12/26/23.
//

#include "rom.hpp"

Rom::Rom()
{
    ifstream romfile("rom.txt");
    int index = 0;
    string line;

    if(romfile.is_open())
    {
        while(getline(romfile, line))
        {
            long romline = (std::bitset<35> (line)).to_ullong();
            rom[index] = translate(romline);

            index++;
        }
    }
}

ROM_SIGNALS Rom::translate(long bitstr)
{
    long bitmask = 0x01;

    ROM_SIGNALS output;

    output.LD_PC = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.LD_MAR = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.LD_MDR = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.LD_REG = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.LD_IR = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.LD_BEN = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.LD_CC = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.GATE_PC = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.GATE_MDR = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.GATE_ALU = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.GATE_MARMUX = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.PCMUX_1 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.PCMUX_2 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.DRMUX_1 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.DRMUX_2 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.SR1MUX_1 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.SR1MUX_2 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.ADDR1MUX = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.ADDR2MUX_1 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.ADDR2MUX_2 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.MARMUX = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.ALUK_1 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.ALUK_2 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.MIO_EN = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.R_W = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.COND0 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.COND1 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.COND2 = bitstr & bitmask;

    bitstr = bitstr >> 1;

    output.IRD = bitstr & bitmask;

    bus j = 0;

    for(int i = 15; i > 9; i--)
    {
        bitstr = bitstr >> 1;

        bit j_i = bitstr & bitmask;

        set_bit(j, i, j_i);

    }

    output.J = j;

    return output;
}

ROM_SIGNALS Rom::read(reg address)
{
    reg bitmask = 1;
    for(int i = 0; i < 64; i++)
    {
        reg temp = address;

        int index = i;

        for(int j = 15; j > 9; j--)
        {
            bit check = index & bitmask;

            set_bit(temp, j, or_gate(and_gate(check, get_bit(temp, j)), and_gate(not_gate(check), not_gate(get_bit(temp, j)))));

            index = index >> 1;
        }

        romdecode[i] = and6(get_bit(temp, 10), get_bit(temp, 11), get_bit(temp, 12), get_bit(temp, 13), get_bit(temp, 14), get_bit(temp, 15));

    }

    int readi = 0;

    for(int i = 0; i < 64; i++)
    {
        readi = romdecode[i] * i;
    }

    return rom[readi];
}

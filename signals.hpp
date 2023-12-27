#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <iostream>

#define uint8_t char
#define int16_t short
#define bit uint8_t
#define reg int16_t
#define bus int16_t
#define MAX_INT 65536
#define VCC 1
#define GND 0
#define BUS_SIZE 16
#define COMB_BIT_SIZE 8

enum CONTROL_SIG {
    LD_PC,
    LD_MAR,
    LD_MDR,
    LD_REG,
    LD_IR,
    LD_BEN,
    LD_CC,
    GATE_PC,
    GATE_MDR,
    GATE_ALU,
    GATE_MARMUX,
    PCMUX_1,
    PCMUX_2,
    DRMUX_1,
    DRMUX_2,
    SR1MUX_1,
    SR1MUX_2,
    ADDR1MUX,
    ADDR2MUX_1,
    ADDR2MUX_2,
    MARMUX,
    ALUK_1,
    ALUK_2,
    MIO_EN,
    R_W
};

int check_index(int index);
bit get_bit(bus b, int index);
void set_bit(bus &b, int index, bit a);
bit combine_bits_three(bit a, bit b, bit c);
void combine_bits(bit &a, bit b, int index);
bit uncombine_bits(bit a, int index);
bus sign_extend(bus b, int len);
bus zero_extend(bus b, int len);

#endif
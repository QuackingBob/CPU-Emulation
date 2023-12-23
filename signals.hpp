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

static bit LD_PC;
static bit LD_MAR;
static bit LD_MDR;
static bit LD_REG;
static bit LD_IR;
static bit LD_BEN;
static bit LD_CC;
static bit GATE_PC;
static bit GATE_MDR;
static bit GATE_ALU;
static bit GATE_MARMUX;
static bit PCMUX_1;
static bit PCMUX_2;
static bit DRMUX_1;
static bit DRMUX_2;
static bit SR1MUX_1;
static bit SR1MUX_2;
static bit ADDR1MUX;
static bit ADDR2MUX_1;
static bit ADDR2MUX_2;
static bit MARMUX;
static bit ALUK_1;
static bit ALUK_2;
static bit MIO_EN;
static bit R_W;

int check_index(int index);
bit get_bit(bus b, int index);
void set_bit(bus &b, int index, bit a);
bit combine_bits_three(bit a, bit b, bit c);
void combine_bits(bit &a, bit b, int index);
bit uncombine_bits(bit a, int index);
bus sign_extend(bus b, int len);
bus zero_extend(bus b, int len);

#endif
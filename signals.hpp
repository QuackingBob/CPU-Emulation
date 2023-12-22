#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <iostream>

#define uint8_t char
#define int16_t short
#define bit uint8_t
#define bus int16_t
#define VCC 1
#define GND 0
#define BUS_SIZE 16
#define COMB_BIT_SIZE 8

int check_index(int index);
bit get_bit(bus b, int index);
void set_bit(bus &b, int index, bit a);
bit combine_bits_three(bit a, bit b, bit c);
void combine_bits(bit &a, bit b, int index);
bit uncombine_bits(bit a, int index);

#endif
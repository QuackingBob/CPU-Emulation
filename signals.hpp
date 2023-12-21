#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <iostream>

#define uint8_t char
#define int16_t short
#define bit uint8_t
#define bus int16_t
#define VCC 1
#define GND 0

int check_index(int index);
bit get_bit(bus b, int index);
void set_bit(bus &b, int index, bit a);

#endif
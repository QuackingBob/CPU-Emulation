#ifndef RAM_HPP
#define RAM_HPP

#include "gates.hpp"
#include "decoder.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class Ram {

private:
    bus memory[65536];



public:
    Ram(bus start);
    void write(bit cs, reg address, bus data);
    bus read(bit cs, reg address);

    void write_to_file();
    void read_from_file();
    void print_to_screen();
};

#endif

#include "ram.hpp"
//#include "rom.hpp"
#include "components.hpp"


class Processor {
public:
    bit clock;
    // need control
    program_counter pc;
    Ram memory;

    int tick();
    Processor(): clock(0), pc(0), memory(0) {};
};
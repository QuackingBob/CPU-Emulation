#include "ram.hpp"
//#include "rom.hpp"
#include "components.hpp"

typedef struct state_transition
{
    int state_count;
    state_transition **transition_states;
    template <typename T> state_transition* (*transition)(T ...);
} state_transition;

class Processor {
private:
    bit clock;
    // need control
    program_counter pc;
    Ram memory;
    state_transition *state;

public: 
    int tick();
    int reset_state();
    int init_state_graph();
    Processor() : clock(0), pc(0), memory(0) {};
    ~Processor();
};
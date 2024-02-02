#include "ram.hpp"
//#include "rom.hpp"
#include "components.hpp"

#include <functional>
#include <unordered_map>

using namespace std;

typedef struct state_transition
{
    int state_count;
    static unordered_map<string, state_transition*> state_map; // this map contains all created states and helps avoid memory leaks
    std::function <state_transition* (void)> &transition;
} state_transition;

state_transition * new_state(int state_num);
class Processor {
private:
    bit clock;
    // need control
    program_counter pc;
    Ram memory;
    state_transition *state;
    INPUT_SIGNALS signals;
    ROM_SIGNALS control_signals;

public: 
    int tick();
    int reset_state();
    int init_state_graph();
    Processor() : clock(0), pc(0), memory(0) {};
    ~Processor();
};
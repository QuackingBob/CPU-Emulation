//
// Created by vvk on 12/26/23.
//

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "components.hpp"
#include "rom.hpp"
#include "signals.hpp"

class Controller
{
private:
    Rom rom;
    ROM_SIGNALS current_state;

public:

    Controller();
    ROM_SIGNALS get_state();
    void next(INPUT_SIGNALS input, instruction_register ir);

};
#endif

//
// Created by vvk on 12/26/23.
//

#ifndef ROM_HPP
#define ROM_HPP

#include "tests.cpp"
#include "ram.hpp"

using namespace std;

class Rom
{
private:
    ROM_SIGNALS rom[64];
    int romdecode[64];
    ROM_SIGNALS translate(long bitstr);

public:
    Rom();
    ROM_SIGNALS read(reg address);

};


#endif

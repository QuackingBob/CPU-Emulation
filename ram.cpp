#include "ram.hpp"

using namespace std;

Ram::Ram(bus start)
{
    for(int i = 0; i < 65536; i++)
    {
        memory[i] = start;
    }
}

void Ram::write(bit cs, reg address, bus data)
{

    inputSignals.R = 0;


    bus chip_select;

    for(int i = 0; i < 16; i++)
    {
        set_bit(chip_select, i, cs);
    }

    decode(address);

    int index = 0;

    for(int i = 0; i < MAX_INT; i++)
    {
        index = decoded[i] * i;
    }

    memory[index] = or_bus(and_bus(data, chip_select), and_bus(memory[index], not_bus(chip_select)));

    inputSignals.R = 1;
}

bus Ram::read(bit cs, reg address)
{

    inputSignals.R = 0;


    bus chip_select;

    for(int i = 0; i < 16; i++)
    {
        set_bit(chip_select, i, cs);
    }

    decode(address);

    int index = 0;

    for(int i = 0; i < MAX_INT; i++)
    {
        index = decoded[i] * i;
    }

    inputSignals.R = 1;

    return memory[index];

}

void Ram::write_to_file()
{
    ofstream ramfile;
    ramfile.open("ram.txt");

    for(int i = 0; i < MAX_INT; i++)
    {
        ramfile << bus_str(memory[i]) << endl;
    }

    ramfile.close();
}

void Ram::read_from_file()
{
    string line;
    ifstream ramfile ("ram.txt");
    int index = 0;

    if(ramfile.is_open())
    {
        while(getline(ramfile, line))
        {
            memory[index] = (std::bitset<16> (std::string(line))).to_ullong();

            index++;
        }
    }
}

void Ram::print_to_screen()
{
    for(int i = 0; i < MAX_INT; i++)
    {
        cout << bus_str(memory[i]) << '\n';
    }
}



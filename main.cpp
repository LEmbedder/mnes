#include <iostream>
#include <sstream>
#include "mos6502.hpp"

int main()
{
    mos6502 cpu(2 * 1024);
    cpu.print_state();

    std::cin.get();
    return 0;
}
